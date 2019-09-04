#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main/interpreter.h"
#define TK_NAME_SIZE 12
#define TK_INITIAL_INDEX 258
#define READABLE 0

extern int yylex();
extern int yylineno;
extern char* yytext;

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
int convertTokenToString(int token, char** str);

int main(void) {
  int ntoken;
  char* str = malloc(sizeof(char)*TK_NAME_SIZE);
  ntoken = yylex();
  int tkcounter = 0;
  printf("tc_expected = { ");
  while (ntoken) {
    if (READABLE && convertTokenToString(ntoken,&str)==1)
    {
      printf( "%s ", str );
    }
    else
    {
      printf( "%d, ", ntoken );
    }
    ++tkcounter;
    ntoken = yylex();
  }
  printf(" }; tc_qtd_tokens = %d;", tkcounter);
  return 0;
}

int convertTokenToString(int token, char** str)
{
  if (token>=TK_INITIAL_INDEX)
  {
    strcpy(*str, tk_names[token-TK_INITIAL_INDEX+1]);
    return 1;
  }
  else if (token>0)
  {
    char c = (char)token;
    char mid[1] = { c};
    strcpy(*str, mid);
    return 1;
  }
  else
    return 0;
}