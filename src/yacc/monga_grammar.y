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

bloco : '{' multi_definicoes multi_comandos '}' ;

multi_definicoes : | defs_variaveis ;

multi_comandos : | comandos ;
