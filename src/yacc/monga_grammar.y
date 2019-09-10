  /*
  * Parser sintático de Monga
  * Rodrigo Leite - 1413150 - 08/setembro/2019
  **/
%{
#include "main/interpreter.h"
%}

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
%token TK_ID
%token TK_STRING
%token TK_INTEGER
%token TK_FLOATING
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

start :
          | programa
          ;

programa :  definicao
          | programa definicao
          ;

definicao : def_variavel
          | def_funcao ;

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

parametros :
           | lista_params ;

lista_params : parametro
             | lista_params ',' parametro;

parametro : TK_ID ':' tipo ;

bloco : '{' multi_defs_opcional multi_comandos_opcional '}' ;

multi_defs_opcional : | defs_variaveis ;

defs_variaveis : def_variavel
               | defs_variaveis def_variavel
               ;

multi_comandos_opcional : | comandos ;

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

exp : TK_INTEGER
    | TK_FLOATING
    | TK_STRING
    | TK_TRUE
    | TK_FALSE
    | var
    | '(' exp ')'
    | exp TK_AS tipo
    | TK_NEW tipo '[' exp ']'
    | '-' exp
    | '!' exp
    | exp TK_AND relacional
    | exp TK_OR relacional
    ;

relacional : relacional TK_EQ aritmetica
           | relacional TK_NE aritmetica
           | relacional TK_LE aritmetica
           | relacional TK_GE aritmetica
           | relacional '<' aritmetica
           | relacional '>' aritmetica
           | aritmetica
           ;

aritmetica: aritmetica '+' parcela
          | aritmetica '-' parcela
          | parcela
          ;

parcela : parcela '*' fator
        | parcela '/' fator
        | fator
        ;

fator : TK_INTEGER
      | TK_FLOATING
      | '(' exp ')'
      ;


chamada : TK_ID '(' lista_opcional_exp ')' ;

lista_opcional_exp : | lista_exp ;

lista_exp : exp
          | lista_exp ',' exp ;
