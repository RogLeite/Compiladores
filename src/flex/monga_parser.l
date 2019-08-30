%{
#include "main/interpreter.h"
%}
%%
[ \t\n]                 ;
as                      return TK_AS;
char                    return TK_CHAR;
else                    return TK_ELSE;
float                   return TK_FLOAT;
if                      return TK_IF;
int                     return TK_INT;
new                     return TK_NEW;
return                  return TK_RETURN;
void                    return TK_VOID;
while                   return TK_WHILE;
[a-zA-Z_][a-zA-Z_0-9]*  return TK_ID;
. printf("Não casou: \"%s\"\n", yytext);
%%

int yywrap(void)
{
  return 1;
}
