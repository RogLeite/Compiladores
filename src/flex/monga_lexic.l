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
%%
[ \t]                           ;
\n                              yylineno++;
as                              {storeLineno(); return TK_AS;}
char                            {storeLineno(); return TK_CHAR;}
else                            {storeLineno(); return TK_ELSE;}
float                           {storeLineno(); return TK_FLOAT; }
if                              {storeLineno(); return TK_IF;}
int                             {storeLineno(); return TK_INT; }
new                             {storeLineno(); return TK_NEW; }
return                          {storeLineno(); return TK_RETURN;}
bool                            {storeLineno(); return TK_BOOL;}
false                           {storeLineno(); return TK_FALSE; }
true                            {storeLineno(); return TK_TRUE;}
while                           {storeLineno(); return TK_WHILE; }
[a-zA-Z_][a-zA-Z_0-9]*          {storeString(); return TK_ID;}
\"([^"\\\n]|\\[nt"\\])*\"       {storeString(); return TK_STRING;}
[0-9]+                          {storeInt(); return TK_INTEGER;}
0[xX]{HEX}+                        {storeInt(); return TK_INTEGER;}
([0-9]+("."[0-9]*)?|"."[0-9]+)([eE][-+]?[0-9]+)?    {storeFloat(); return TK_FLOATING;}
0x({HEX}+("."{HEX}*)?|"."{HEX}+)([pP][-+]?[0-9]+)?  {storeFloat(); return TK_FLOATING;}

[-+*/,:;(){}=@<>]               {storeLineno(); return (int)*yytext;}
"["|"]"                         {storeLineno(); return (int)*yytext;}
"=="                            {storeLineno(); return TK_EQ;}
"~="                            {storeLineno(); return TK_NE;}
"<="                            {storeLineno(); return TK_LE;}
">="                            {storeLineno(); return TK_GE;}
"&&"                            {storeLineno(); return TK_AND;}
"||"                            {storeLineno(); return TK_OR;}
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
void storeLineno()
{
  yylval.i = yylineno;
}
int yywrap(void)
{
  return 1;
}
