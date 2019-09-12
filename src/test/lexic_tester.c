/*
* Testador do léxico de Monga
* Rodrigo Leite - 1413150 - 08/setembro/2019
**/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main/interpreter.h"
#define READABLE 0
#ifdef TC_LEXIC_TOKENS

char* tc_name = "test_lexic_tokens.txt";
int tc_qtd_tokens = 183;
int tc_expected [183] = { 258, 259, 260, 261, 262, 263, 264, 265, 266, 278, 279, 267, 272, 273, 274, 275, 276, 277, 269, 45, 45, 45, 43, 43, 43, 42, 47, 44, 58, 59, 40, 41, 123, 125, 61, 64, 60, 62, 91, 93, 269, 269, 269, 269, 269, 269, 263, 270, 270, 270, 270, 270, 270, 270, 261, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 261, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 266, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271, 271 };

#elif TC_FIB10

char* tc_name = "test_fibonacci.mng";
int tc_qtd_tokens = 138;
int tc_expected [138] = { 268, 40, 268, 58, 263, 41, 58, 91, 263, 93, 123, 262, 268, 60, 270, 123, 268, 58, 263, 91, 93, 59, 268, 61, 264, 263, 91, 270, 93, 59, 268, 91, 270, 93, 61, 45, 270, 59, 265, 268, 59, 125, 268, 58, 263, 59, 268, 58, 263, 91, 93, 59, 64, 270, 59, 64, 270, 59, 268, 61, 270, 59, 268, 61, 264, 263, 91, 268, 93, 59, 268, 91, 270, 93, 61, 270, 59, 268, 91, 270, 93, 61, 270, 59, 267, 268, 60, 268, 123, 64, 268, 59, 268, 91, 268, 93, 61, 268, 91, 268, 45, 270, 93, 43, 268, 91, 268, 45, 270, 93, 59, 268, 61, 268, 43, 270, 59, 125, 265, 268, 59, 125, 268, 40, 41, 58, 263, 123, 64, 268, 40, 270, 41, 59, 265, 270, 59, 125,  };
#elif TC_SIMPLEMAIN

char* tc_name = "test_simple_main.mng";
int tc_qtd_tokens = 18;
int tc_expected[18] = { 268, 40, 41, 58, 263, 123, 268, 58, 263, 59, 268, 61, 270, 59, 265, 268, 59, 125 };

#endif



extern int yylex();
extern int yylineno;
extern char* yytext;

int main(void) {
  int passed = 1;
  int ntoken;
  ntoken = yylex();
  int tkcounter = 0;
  printf("-----------------------------------\n");
  printf("TESTING \"%s\" \n", tc_name);
  while (ntoken && tkcounter < tc_qtd_tokens) {
    if(ntoken != tc_expected[tkcounter])
    {
      printf("Incorrect token Numero:%d in line l:%d\n", ntoken, yylineno);
      passed = 0;
      break;
    }
    ++tkcounter;
    ntoken = yylex();
  }
  if (tc_qtd_tokens != tkcounter && passed == 1)
  {
    passed = 0;
    printf("Expected %d tokens\n", tc_qtd_tokens);
    printf("Counted %d tokens\n", tkcounter);
  }
  if(passed == 0)
  {
    printf("!!!!!!!!!!!!!!!\n");
    printf("Test case \"%s\" FAILED\n", tc_name);
    printf("!!!!!!!!!!!!!!!\n");
  }
  else
    printf("Test \"%s\" Passed\n", tc_name);

  return 0;
}
