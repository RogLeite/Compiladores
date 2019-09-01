%{
#include "main/interpreter.h"
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
void                            return TK_VOID;
while                           return TK_WHILE;
[a-zA-Z_][a-zA-Z_0-9]*          return TK_ID;
\"([^"\\\n]|\\[nt"\\])*\"       return TK_STRING;
[0-9]+                          return TK_INTEGER;
0x{HEX}+                        return TK_INTEGER;
([0-9]+("."[0-9]*)?|"."[0-9]+)([eE][-+]?[0-9]+)?    return TK_FLOATING;
0x({HEX}+("."{HEX}*)?|"."{HEX}+)([pP][-+]?[0-9]+)?  return TK_FLOATING;

#[^\n]* printf("Comentário: \"%s\"\n", yytext);
. printf("Não casou: \"%s\" Line: %i\n", yytext, yylineno);
%%

int yywrap(void)
{
  return 1;
}
