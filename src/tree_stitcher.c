/*
* Testador do léxico de Monga
* Rodrigo Leite - 1413150 - 08/setembro/2019
**/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ast.h"
#include "interpreter.h"


int main(void)
{
  printf("\n");
  if(yyparse()==0)
  {
    printf("Programa parsed com sucesso!\n");
#ifdef PRINT_TREES
    printTree(getGlobalTree(),0);
    printf("\n");
#endif
    if(stitchTree(getGlobalTree())==-1)
      printf("Árvore não foi costurada com sucesso\n");
    printTree(getGlobalTree(),0);
    printf("\n");
  }
  else
    printf("Programa não foi parsed :C\n");

  printf("\n-----------------------------------------\n-----------------------------------------\n");
  return 0;
}
