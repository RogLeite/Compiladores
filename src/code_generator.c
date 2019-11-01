/*
* Gerador de código para a árvore sintática
* Rodrigo Leite - 1413150 - 27/outubro/2019
**/
#include "ast.h"
#include <stdio.h>
#include <assert.h>


void generateGlobalCode(FILE *outfile);
void generateDefinitionsCode(FILE *outfile, Node *tree);
void generateFuncdefCode(FILE *outfile, Node *tree);

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

void generateGlobalCode(FILE *outfile)
{
  Node *tree = getGlobalTree();
  assert(tree != NULL);
  switch (tree->tag) {
    case FUNCDEF:
      generateFuncdefCode(outfile, getValueNode(tree));
      break;
    case DEFS:
      generateDefinitionsCode(outfile, getValueNode(tree));
      if(getSecondNode(tree)->tag == FUNCDEF)
      {
        generateFuncdefCode(outfile, getSecondNode(tree));
      }
      break;
    default:
      fprintf(outfile, "case %s não implementado em generateGlobalCode()\n", tag_name[tree->tag]);
  }
  fprintf(outfile, "\n");
}
void generateDefinitionsCode(FILE *outfile, Node *tree)
{
  fprintf(outfile, "generateDefinitionsCode() não implementado\n");
}
void generateFuncdefCode(FILE *outfile, Node *tree)
{
  fprintf(outfile, "generateFuncdefCode() não implementado\n");
}
