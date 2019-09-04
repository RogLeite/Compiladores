#include <stdio.h>
#include "tester.h"
#include "interpreter.h"



extern int yylex();
extern int yylineno;
extern char* yytext;
char* test_name;
int result[];

int main(void) {
  int ntoken;
  ntoken = yylex();
  int tkcounter = 0;
  while (ntoken) {
    if (ntoken != result[tkcounter])
    {
      printf("FAILED: ");
      printf("%s",test_name);
      printf(" in token number %d at line: %d\n", tkcounter, yylineno);
      printf("\tyytext = %s\n", yytext);
      printf("\tntoken = %d\n", ntoken);
      printf("\tresult[i] = %d\n", result[tkcounter]);

      return 0;
    }
    ++tkcounter;
    ntoken = yylex();
  }
  printf("Passed: ");
  printf("%s",test_name);
  printf("\n");
  return 0;
}
