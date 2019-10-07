#ifndef VAR_TABLE_H
#define VAR_TABLE_H

#include "ast.h"

/*retorna indice do escopo corrente*/
int enterScope();

/*
retorna índice do escopo corrente
ou -1 para indicar que não há escopo para sair
*/
int leaveScope();

/**
  retorna 0 se tudo deu certo
  retorna outra coisa se deu errado
*/
int newId(char *name, Node *node);

/*
retorna NULL se não encontrou o nome
retorna o ponteiro se encontrou
*/
Node *getId(char *id);

#endif
