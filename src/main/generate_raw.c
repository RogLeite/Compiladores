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
          "TK_SYMBOL"
};

int main(void) {
  int ntoken, vtoken;
  ntoken = yylex();
  printf("int[ x ] = {");
  int tkcounter = 0;
  while (ntoken) {
    printf("%s, ", names[ntoken]);
    ++tkcounter;
    ntoken = yylex();
  }
  printf("}; x = %d;", tkcounter);
  return 0;
}
