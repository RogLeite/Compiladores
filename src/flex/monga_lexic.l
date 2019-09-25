  /*
  * Parser léxico de Monga
  * Rodrigo Leite - 1413150 - 08/setembro/2019
  **/
%{
#include "main/ast.h"
#include "main/interpreter.h"
#include <string.h>
#include <stdlib.h>
void storeString();
void storeInt();
void storeFloat();
%}
HEX       [0-9A-Fa-f]
HEXNOZ    [1-9A-Fa-f]
%%
[ \t]                           ;
\n                              yylineno++;
as                              return TK_AS;
char                            return TK_CHAR;
else                            return TK_ELSE;
float                           return TK_FLOAT;
if                              return TK_IF;
int                             return TK_INT;
new                             return TK_NEW;
return                          return TK_RETURN;
bool                            return TK_BOOL;
false                           return TK_FALSE;
true                            return TK_TRUE;
while                           return TK_WHILE;
[a-zA-Z_][a-zA-Z_0-9]*          {storeString(); return TK_ID;}
\"([^"\\\n]|\\[nt"\\])*\"       {storeString(); return TK_STRING;}
[0-9]+                          {storeInt(); return TK_INTEGER;}
0x{HEX}+                        {storeInt(); return TK_INTEGER;}
([0-9]+("."[0-9]*)?|"."[0-9]+)([eE][-+]?[0-9]+)?    {storeFloat(); return TK_FLOATING;}
0x({HEX}+("."{HEX}*)?|"."{HEX}+)([pP][-+]?[0-9]+)?  {storeFloat(); return TK_FLOATING;}

[-+*/,:;(){}=@<>]               return (int)*yytext;
"["|"]"                         return (int)*yytext;
"=="                            return TK_EQ;
"~="                            return TK_NE;
"<="                            return TK_LE;
">="                            return TK_GE;
"&&"                            return TK_AND;
"||"                            return TK_OR;
#[^\n]*                         ;
. printf("MISMATCH: \"%s\" Line: %i\n", yytext, yylineno);
%%

void storeString()
{
  char* str = malloc(strlen(yytext)*sizeof(char));
  int i = 0;
  while(yytext[i] != '\0')
  {
    if (yytext[i] != '\\')
    {
      str[i] = yytext[i];
    }
    else
    {
      switch (yytext[i+1])
      {
        case 'n' :
          str[i] = '\n';
        break;
        case 't' :
          str[i] = '\t';
        break;
        case '\"' :
          str[i] = '\"';
        break;
        case '\\' :
          str[i] = '\\';
        break;
      }
    }
    ++i;
  }
  yylval.s = str;
}
void storeInt()
{
  yylval.i = atoi(yytext);
}
void storeFloat()
{
  yylval.d = strtod(yytext, (char**) NULL);
}
int yywrap(void)
{
  return 1;
}
