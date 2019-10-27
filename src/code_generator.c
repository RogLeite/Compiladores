/*
* Gerador de código para a árvore sintática
* Rodrigo Leite - 1413150 - 27/outubro/2019
**/
#include "ast.h"
#include <stdio.h>
#include <assert.h>

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
    default:
      fprintf(outfile, "case %s não implementado em generateGlobalCode()\n", tag_name[tree->tag]);
  }
}
