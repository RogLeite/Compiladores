#include <stdio.h>
#include "interpreter.h"

extern int yylex();
extern int yylineno;
extern char* yytext;
extern char* test_name;
extern int result[];

int main(void) {
  int ntoken;
  ntoken = yylex();
  int tkcounter = 0;
  while (ntoken) {
    ++tkcounter;
    if (ntoken != result[tkcounter])
    {
      printf("FAILED: ");
      printf("%s",test_name);
      printf(" in token number %d at line: %d\n", tkcounter, yylineno);
      printf("\tyytext = %s\n", yytext);
      return 0;
    }
    ntoken = yylex();
  }
  printf("Passed: ");
  printf("%s",test_name);
  printf("\n");
  return 0;
}
