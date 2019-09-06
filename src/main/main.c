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
          "TK_BOOL",
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

int main(void) {
  int ntoken, vtoken;
  ntoken = yylex();
  while (ntoken) {
    printf("%s\n", names[ntoken]);
    ntoken = yylex();
  }
  return 0;
}
