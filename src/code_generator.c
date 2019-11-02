/*
* Gerador de código para a árvore sintática
* Rodrigo Leite - 1413150 - 27/outubro/2019
**/
#include "ast.h"
#include <stdio.h>
#include <assert.h>


void codeGlobal(FILE *outfile);
void codeGlobalId(FILE *outfile, char *id);
void codeType(FILE *outfile, Node *typeTree);
void codeDefinitions(FILE *outfile, Node *tree);
void codeParamDefs(FILE *outfile, Node *tree);
void codeFuncdef(FILE *outfile, Node *tree);
void codeFuncBody(FILE *outfile, Node *tree);

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

void codeType(FILE *outfile, Node *typeTree)
{
  if(typeTree==NULL)
  {
    fprintf(outfile, "void ");
  }
  else
  {
    switch (typeTree->tag) {
      default:
        fprintf(outfile, ";case %s não implementado em codeType()\n", tag_name[typeTree->tag]);
    }
  }
}

void codeDefinitions(FILE *outfile, Node *tree)
{
  fprintf(outfile, ";codeDefinitions() não implementado\n");
}

void codeParamDefs(FILE *outfile, Node *tree)
{
  switch(tree->tag)
  {
    case EMPTY:
      fprintf(outfile, "() ");
      break;
    default:
      fprintf(outfile, ";case %s não implementado em codeParamDefs()\n", tag_name[tree->tag]);
      break;
  }
}

void codeFuncdef(FILE *outfile, Node *tree)
{
  fprintf(outfile, "define ");
  codeType(outfile, getType(tree));
  codeGlobalId(outfile, getNodeId(tree));
  codeParamDefs(outfile, getSecondNode(tree));
  fprintf(outfile, "#0 ");
  codeFuncBody(outfile, tree);
}

void codeFuncBody(FILE *outfile, Node *tree)
{
  //Node *block = getFourthNode(tree);
  fprintf(outfile, "{\n\tret void\n}\n");
  fprintf(outfile, ";codeFuncBody() não implementado\n");
}
