#include <stdio.h>
#include "interpreter.h"

extern int yylex();
extern int yylineno;
extern char* yytext;

char* names[] = {
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
          "TK_ID"
};

int main(void) {
  int ntoken, vtoken;
  ntoken = yylex();
  while (ntoken) {
    printf("%s\n", names[ntoken]);
    ntoken = yylex();
  }
  return 0;
}
