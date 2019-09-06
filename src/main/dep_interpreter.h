#ifndef INTERPRETER_H
#define INTERPRETER_H

typedef enum token {
  //palavras reservadas
  TK_AS = 256,
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
  TK_STRING,
  TK_INTEGER,
  TK_FLOATING,
  TK_EQ,
  TK_NE,
  TK_LE,
  TK_GE,
  TK_AND,
  TK_OR,
} Token;

#endif
