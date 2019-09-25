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
    printf("Parsed the program!\n");
  else
    printf("Did not parse the program :C\n");
  return 0;
}
