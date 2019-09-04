#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tester.h"
#include "main/interpreter.h"
#define READABLE 0
#ifdef TC_FIB10

char* tc_name = "fibonacci10";
int tc_qtd_tokens = 138;
int tc_expected [138] = { 268, 40, 268, 58, 263, 41, 58, 263, 91, 93, 123, 262, 268, 60, 270, 123, 268, 58, 263, 91, 93, 59, 268, 61, 264, 263, 91, 270, 93, 59, 268, 91, 270, 93, 61, 45, 270, 59, 265, 268, 59, 125, 268, 58, 263, 59, 268, 58, 263, 91, 93, 59, 64, 270, 59, 64, 270, 59, 268, 61, 270, 59, 268, 61, 264, 263, 91, 268, 93, 59, 268, 91, 270, 93, 61, 270, 59, 268, 91, 270, 93, 61, 270, 59, 267, 268, 60, 268, 123, 64, 268, 59, 268, 91, 268, 93, 61, 268, 91, 268, 45, 270, 93, 43, 268, 91, 268, 45, 270, 93, 59, 268, 61, 268, 43, 270, 59, 125, 265, 268, 59, 125, 268, 40, 41, 58, 263, 123, 64, 268, 40, 270, 41, 59, 265, 270, 59, 125,  };

#elif TC_SIMPLEMAIN

char* tc_name = "simple_main";
int tc_qtd_tokens = 18;
int tc_expected[18] = { 268, 40, 41, 58, 263, 123, 268, 58, 263, 59, 268, 61, 270, 59, 265, 268, 59, 125,  };

#endif



extern int yylex();
extern int yylineno;
extern char* yytext;

int main(void) {
  int ntoken;
  ntoken = yylex();
  int tkcounter = 0;
  printf("tc_name = %s\n",tc_name );
  printf("tc_qtd_tokens = %d\n", tc_qtd_tokens);
  // while (ntoken) {
  //
  //   ++tkcounter;
  //   ntoken = yylex();
  // }
  return 0;
}
