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
    printf("\nARVORE DO PROGRAMA:\n");
    printTree(getGlobalTree(),0);
#endif
  }
  else
    printf("Programa não foi parsed :C\n");

  printf("\n-----------------------------------------\n-----------------------------------------\n");
  return 0;
}