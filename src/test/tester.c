#include <stdio.h>
#include "tester.h"
#include "interpreter.h"



extern int yylex();
extern int yylineno;
extern char* yytext;
char* test_name;
int result[];

char* tk_names[] = {
          NULL,
          "TK_AS",
          "TK_CHAR",
          "TK_ELSE",
          "TK_FLOAT",
          "TK_IF",
          "TK_INT",
          "TK_NEW",
          "TK_RETURN",
          "TK_VOID",
          "TK_WHILE",
          "TK_ID",
          "TK_STRING",
          "TK_INTEGER",
          "TK_FLOATING",
          "TK_EQ",
          "TK_NE",
          "TK_LE",
          "TK_GE",
          "TK_AND",
          "TK_OR"
};
char* convertTokenToString(int token);

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

char* convertTokenToString(int token)
{
  if (token>=258)
  {

  }
  else
  {
    return (char) token;
  }
}
