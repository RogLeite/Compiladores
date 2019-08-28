#ifndef INTERPRETER_H
#define INTERPRETER_H

typedef enum token {
  //palavras reservadas
  TK_AS,
  TK_CHAR,
  TK_ELSE,
  TK_FLOAT,
  TK_IF,
  TK_INT,
  TK_NEW,
  TK_RETURN,
  TK_VOID,
  TK_WHILE,
  //
  TK_ID,
} Token;



#endif
