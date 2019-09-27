  /*
  * Parser sintático de Monga
  * Rodrigo Leite - 1413150 - 08/setembro/2019
  **/
%{
#include <stdio.h>
#include <string.h>
#include "main/ast.h"
#include "main/interpreter.h"
#include "main/lex_defs.h"

void yyerror(const char *s);

%}

%union {
  int i;
  double d;
  char *s;
  Node *n;
}
%define parse.error verbose
%token <i> TK_AS
%token <i> TK_CHAR
%token <i> TK_ELSE
%token <i> TK_FLOAT
%token <i> TK_IF
%token <i> TK_INT
%token <i> TK_NEW
%token <i> TK_RETURN
%token <i> TK_BOOL
%token <i> TK_WHILE
%token <s> TK_ID
%token <s> TK_STRING
%token <i> TK_INTEGER
%token <d> TK_FLOATING
%token <i> TK_EQ
%token <i> TK_NE
%token <i> TK_LE
%token <i> TK_GE
%token <i> TK_AND
%token <i> TK_OR
%token <i> TK_FALSE
%token <i> TK_TRUE
%token <i> '-' '+' '*' '/' '!' ',' ':' ';' '(' ')' '{' '}' '=' '@' '<' '>' '[' ']'

%type <n> programa definicao def_variavel tipo def_funcao parametros lista_params
%type <n> parametro bloco defs_variaveis comandos comando var exp exp_and exp_igualdade
%type <n> exp_comparativa exp_aditiva exp_multiplicativa exp_as exp_new exp_unaria
%type <n> fator constante chamada lista_opcional_exp lista_exp

%start start
%%

start : %empty
      | programa {global_tree = $1;}
      ;

programa : definicao            {$$ = $1;}
         | programa definicao   {$$ = mkBiNode(DEFS, $1, $2);}
         ;

definicao : def_variavel  {$$ = $1;}
          | def_funcao    {$$ = $1;}
          ;

def_variavel : TK_ID ':' tipo ';' {$$ = mkIdUniNode(VARDEC, $1, $3);};

tipo : TK_INT       {$$ = mkIntTypeNode();}
     | TK_CHAR      {$$ = mkCharTypeNode();}
     | TK_FLOAT     {$$ = mkFloatTypeNode();}
     | TK_BOOL      {$$ = mkBoolTypeNode();}
     | '[' tipo ']' {$$ = mkUniNode(ARRAYDEC, $2);}
     ;

def_funcao : TK_ID '(' parametros ')' ':' tipo bloco {$$ = mkIdTriNode(TYPEDFUNCDEF, $1, $3, $6, $7);}
           | TK_ID '(' parametros ')' bloco          {$$ = mkIdBiNode(FUNCDEF, $1, $3, $5);}
           ;

parametros : %empty       {$$ = NULL;}
           | lista_params {$$ = $1;}
           ;

lista_params : parametro                    {$$ = $1;}
             | lista_params ',' parametro   {$$ = mkBiNode(PARAMLIST, $1, $3);}
             ;

parametro : TK_ID ':' tipo  {$$ = mkIdUniNode(PARAM, $1, $3);};

bloco : '{' '}'                         {$$ = mkLeafNode(BLOCK);}
      | '{' comandos '}'                {$$ = mkUniNode(BLOCK, $2);}
      | '{' defs_variaveis '}'          {$$ = mkUniNode(BLOCK, $2);}
      | '{' defs_variaveis comandos '}' {$$ = mkBiNode(BLOCK, $2, $3);}
      ;


defs_variaveis : def_variavel                 {$$ = $1;}
               | defs_variaveis def_variavel  {$$ = mkBiNode(VARDECS, $1, $2);}
               ;

comandos : comando              {$$ = $1;}
         | comandos comando     {$$ = mkBiNode(COMMANDS, $1, $2);}
         ;

comando : TK_IF exp bloco TK_ELSE bloco {$$ = mkTriNode(IFELSE, $2, $3, $5);}
        | TK_IF exp bloco               {$$ = mkBiNode(IF, $2, $3);}
        | TK_WHILE exp bloco            {$$ = mkBiNode(WHILE, $2, $3);}
        | var '=' exp ';'               {$$ = mkBiNode(ASSIGN, $1, $3);}
        | TK_RETURN exp ';'             {$$ = mkUniNode(RETVAL, $2);}
        | TK_RETURN ';'                 {$$ = mkLeafNode(RET);}
        | chamada ';'                   {$$ = $1;}
        | '@' exp ';'                   {$$ = mkUniNode(PRINT, $2);}
        | bloco                         {$$ = $1;}
        ;

var : TK_ID                {$$ = mkIdLeafNode(SIMPLEVAR, $1);}
    | fator '[' exp ']'    {$$ = mkBiNode(ARRAYVAR, $1, $3);}
    ;

exp : exp_and TK_OR exp    {$$ = mkBiNode(OR, $1, $3);}
    | exp_and              {$$ = $1;}
    ;

exp_and : exp_igualdade TK_AND exp_and  {$$ = mkBiNode(AND, $1, $3);}
        | exp_igualdade                 {$$ = $1;}
        ;

exp_igualdade : exp_comparativa TK_EQ exp_igualdade {$$ = mkBiNode(EQUAL, $1, $3);}
              | exp_comparativa TK_NE exp_igualdade {$$ = mkBiNode(NOTEQUAL, $1, $3);}
              | exp_comparativa                     {$$ = $1;}
              ;

exp_comparativa : exp_aditiva TK_LE exp_aditiva {$$ = mkBiNode(LESSOREQUAL, $1, $3);}
                | exp_aditiva TK_GE exp_aditiva {$$ = mkBiNode(GREATEROREQUAL, $1, $3);}
                | exp_aditiva '<' exp_aditiva   {$$ = mkBiNode(LESS, $1, $3);}
                | exp_aditiva '>' exp_aditiva   {$$ = mkBiNode(GREATER, $1, $3);}
                | exp_aditiva                   {$$ = $1;}
                ;

exp_aditiva : exp_multiplicativa '+' exp_aditiva  {$$ = mkBiNode(ADD, $1, $3);}
            | exp_multiplicativa '-' exp_aditiva  {$$ = mkBiNode(SUBTRACT, $1, $3);}
            | exp_multiplicativa                  {$$ = $1;}
            ;

exp_multiplicativa : exp_as '*' exp_multiplicativa  {$$ = mkBiNode(MULTIPLY, $1, $3);}
                   | exp_as '/' exp_multiplicativa  {$$ = mkBiNode(DIVIDE, $1, $3);}
                   | exp_as                         {$$ = $1;}
                   ;

exp_as : exp_new TK_AS tipo   {$$ = mkBiNode(CAST, $1, $3);}
       | exp_new              {$$ = $1;}
       ;

exp_new : TK_NEW tipo '[' exp ']' {$$ = mkBiNode(NEW, $2, $4);}
        | exp_unaria              {$$ = $1;}
        ;

exp_unaria : '!' fator     {$$ = mkUniNode(NOT, $2);}
           | '-' fator     {$$ = mkUniNode(NEGATIVE, $2);}
           | fator         {$$ = $1;}
           ;

fator : constante   {$$ = $1;}
      | '(' exp ')' {$$ = $2;}
      | chamada     {$$ = $1;}
      | var         {$$ = $1;}
      ;

constante : TK_STRING {$$ = mkCteStringNode(STRING, $1);}
        | TK_TRUE     {$$ = mkTrueValueNode();}
        | TK_FALSE    {$$ = mkFalseValueNode();}
        | TK_INTEGER  {$$ = mkCteIntegerNode(INTEGER, $1);}
        | TK_FLOATING {$$ = mkCteFloatingNode(FLOATING, $1);}
        ;

chamada : TK_ID '(' lista_opcional_exp ')' {$$ = mkIdUniNode(CALL, $1, $3);} ;

lista_opcional_exp : %empty     {$$ = NULL;}
                   | lista_exp  {$$ = $1;}
                   ;

lista_exp : exp                 {$$ = $1;}
          | lista_exp ',' exp   {$$ = mkBiNode(LISTEXP, $1, $3);}
          ;
%%

void yyerror (const char *s){fprintf(stderr, "%s\n", s);}
