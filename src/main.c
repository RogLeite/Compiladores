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

    if(stitchTree(getGlobalTree())==-1)
      printf("Árvore não foi costurada com sucesso\n");
    else
    {
      FILE *outfile;
      typeTree(getGlobalTree(), NULL);
      outfile = fopen("Program.ll","w");
      codeGlobal(outfile);
      fclose(outfile);
      printf("\n");
    }
  }
  else
    printf("Programa não foi parsed :C\n");

  return 0;
}
