/*
* Testador do léxico de Monga
* Rodrigo Leite - 1413150 - 08/setembro/2019
**/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main/ast.h"
#include "main/interpreter.h"


int main(void)
{
  if(yyparse()==0)
  {
    printf("Parsed the program!\n");
    printTree(getGlobalTree(),0);
    printf("\n");
  }
  else
    printf("Did not parse the program :C\n");
  return 0;
}
