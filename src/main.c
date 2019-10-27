/*
* Main do compilador de monga
* Rodrigo Leite - 1413150 - 27/outubro/2019
**/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ast.h"
#include "interpreter.h"
#include "code_generator.h"

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
    else
    {
      typeTree(getGlobalTree(), NULL);
      generateGlobalCode(stdout);
      printf("\n");
    }
  }
  else
    printf("Programa não foi parsed :C\n");

  printf("\n-----------------------------------------\n-----------------------------------------\n");
  return 0;
}
