/*
* Gerador de código para a árvore sintática
* Rodrigo Leite - 1413150 - 27/outubro/2019
**/
#include "ast.h"
#include <stdio.h>
#include <assert.h>


void codeGlobal(FILE *outfile);
void codeGlobalId(FILE *outfile, char *id);
void codeDefinitions(FILE *outfile, Node *tree);
void codeFuncdef(FILE *outfile, Node *tree);

int temporario = 0;
int newTemporario()
{
  return temporario++;
}
void printTemporario(int tmp)
{
    printf("a%d", tmp);
}
int printNewTemporario()
{
  int novo = newTemporario();
  printf("a%d", novo);
  return novo;
}

void codeGlobal(FILE *outfile)
{
  Node *tree = getGlobalTree();
  assert(tree != NULL);
  switch (tree->tag) {
    case FUNCDEF:
      codeFuncdef(outfile, getValueNode(tree));
      break;
    case DEFS:
      codeDefinitions(outfile, getValueNode(tree));
      if(getSecondNode(tree)->tag == FUNCDEF)
      {
        codeFuncdef(outfile, getSecondNode(tree));
      }
      break;
    default:
      fprintf(outfile, ";case %s não implementado em codeGlobal()\n", tag_name[tree->tag]);
  }
  fprintf(outfile, "\n");
}

void codeGlobalId(FILE *outfile, char *id)
{
  fprintf(outfile, "@%s", id);
}

void codeDefinitions(FILE *outfile, Node *tree)
{
  fprintf(outfile, ";codeDefinitions() não implementado\n");
}

void codeFuncdef(FILE *outfile, Node *tree)
{
  codeGlobalId(outfile, getNodeId(tree));
  fprintf(outfile, ";codeFuncdef() não implementado\n");
}
