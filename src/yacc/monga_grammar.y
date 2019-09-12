  /*
  * Parser sintático de Monga
  * Rodrigo Leite - 1413150 - 08/setembro/2019
  **/
%{
#include <stdio.h>
#include "main/interpreter.h"
#include "main/lex_defs.h"
void yyerror(const char *s);
%}

%union {
  long i;
  double d;
  char* s;
}
%define parse.error verbose
%token TK_AS
%token TK_CHAR
%token TK_ELSE
%token TK_FLOAT
%token TK_IF
%token TK_INT
%token TK_NEW
%token TK_RETURN
%token TK_BOOL
%token TK_WHILE
%token <s> TK_ID
%token <s> TK_STRING
%token <i> TK_INTEGER
%token <d> TK_FLOATING
%token TK_EQ
%token TK_NE
%token TK_LE
%token TK_GE
%token TK_AND
%token TK_OR
%token TK_FALSE
%token TK_TRUE
%start start
%%

start : %empty
      | programa
      ;

programa : definicao
         | programa definicao
         ;

definicao : def_variavel
          | def_funcao
          ;

def_variavel : TK_ID ':' tipo ';' ;

tipo : TK_INT
     | TK_CHAR
     | TK_FLOAT
     | TK_BOOL
     | '[' tipo ']'
     ;

def_funcao : TK_ID '(' parametros ')' ':' tipo bloco
           | TK_ID '(' parametros ')' bloco
           ;

parametros : %empty
           | lista_params ;

lista_params : parametro
             | lista_params ',' parametro;

parametro : TK_ID ':' tipo ;

bloco : '{' '}'
      | '{' comandos '}'
      | '{' defs_variaveis '}'
      | '{' defs_variaveis comandos '}'
      ;


defs_variaveis : def_variavel
               | defs_variaveis def_variavel
               ;

comandos : comando
         | comandos comando
         ;

comando : TK_IF exp bloco TK_ELSE bloco
        | TK_IF exp bloco
        | TK_WHILE exp bloco
        | var '=' exp ';'
        | TK_RETURN exp ';'
        | TK_RETURN ';'
        | chamada ';'
        | '@' exp ';'
        | bloco
        ;

var : TK_ID
    | exp '[' exp ']'
    ;

exp : var
    | exp TK_AS tipo
    | chamada
    | TK_NEW tipo '[' exp ']'
    | exp TK_OR exp_and
    | exp_and
    ;

exp_and : exp_and TK_AND exp_igualdade
        | exp_igualdade
        ;

exp_igualdade : exp_igualdade TK_EQ exp_comparativa
              | exp_igualdade TK_NE exp_comparativa
              | exp_comparativa
              ;

exp_comparativa : exp_comparativa TK_LE exp_aditiva
                | exp_comparativa TK_GE exp_aditiva
                | exp_comparativa '<' exp_aditiva
                | exp_comparativa '>' exp_aditiva
                | exp_aditiva
                ;

exp_aditiva : exp_aditiva '+' exp_multiplicativa
            | exp_aditiva '-' exp_multiplicativa
            | exp_multiplicativa
            ;

exp_multiplicativa : exp_multiplicativa '*' exp_unaria
                   | exp_multiplicativa '/' exp_unaria
                   | exp_unaria
                   ;

exp_unaria : '!' fator
           | '-' fator
           | fator
           ;

fator : TK_STRING
      | TK_TRUE
      | TK_FALSE
      | TK_INTEGER
      | TK_FLOATING
      | '(' exp ')'
      ;


chamada : TK_ID '(' lista_opcional_exp ')' ;

lista_opcional_exp : %empty
                   | lista_exp
                   ;

lista_exp : exp
          | lista_exp ',' exp
          ;
%%

void yyerror (const char *s){fprintf(stderr, "%s\n", s);}
