%{
#include "main/interpreter.h"
%}
%%
parse_name      printf("parse.l");
uname           printf( "%s", getlogin() );
[hH]ello" "[wW]orld   printf("goodbye");
.               ;
%%

char* getlogin()
{
  return "rleite";
}

int yywrap(void)
{
  return 1;
}
