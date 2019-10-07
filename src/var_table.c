/*
* Tabela de Variáveis para costura da ast.h
* Rodrigo Leite - 1413150 - 07/Outubro/2019
**/
#include "var_table.h"
#include "ast.h"
#include <stdlib.h>
#include <string.h>

typedef struct pilha_s Empilhavel;
void push(Empilhavel *);
Empilhavel *pop();

typedef enum stack_tag
{
  SCOPE = 0,
  VAR
} StackTag;

typedef struct id_node_pair
{
  char *id;
  Node *node;
}IdNodePair;

typedef union conteudo_u
{
  int scope;
  IdNodePair pair;
}Conteudo;

typedef struct pilha_s
{
  StackTag tag;
  Conteudo val;
  Empilhavel *next;
}Empilhavel;

//1 se true 0 se false
int isIdInScope(char *id);

int scopeCounter = 0;
Empilhavel *topo = NULL;

int enterScope()
{
  Empilhavel *novo = (Empilhavel *)malloc(sizeof(Empilhavel));
  novo->tag = SCOPE;
  novo->val.scope = scopeCounter;
  scopeCounter++;
  push(novo);
  return scopeCounter;
}

int leaveScope()
{
  if(scopeCounter<1)
  {
    return -1;
  }
  for(Empilhavel *curr=topo;curr->tag!=SCOPE;curr = topo->next)
  {
    Empilhavel *popped = pop();
    free(popped->val.pair.id);
    free(popped);
  }
  free(pop());
  scopeCounter--;
  return scopeCounter;
}

int newId(char *name, Node *node)
{
  Empilhavel *novo;
  char *id;
  if(isIdInScope(name))
    return -1;

  novo = (Empilhavel*)malloc(sizeof(Empilhavel));
  if (novo == NULL) return -1;

  novo->tag = VAR;

  id = (char*)malloc(sizeof(char)*(strlen(name)+1));
  if (id == NULL) return -1;

  strcpy(novo->val.pair.id, name);
  novo->val.pair.node = node;
  push(novo);
  return 0;
}

Node *getId(char *id)
{
  for(Empilhavel *curr=topo;curr!=NULL;curr = topo->next)
  {
    if(curr->tag==VAR && strcmp(id, curr->val.pair.id)==0)
      return curr->val.pair.node;
  }
  return NULL;
}

void push(Empilhavel *bloco)
{
  bloco->next = topo;
  topo = bloco;
}

Empilhavel *pop()
{
  Empilhavel *no = topo;
  if(topo==NULL)
    return NULL;
  topo = no->next;
  return no;
}

int isIdInScope(char *id)
{
  for(Empilhavel *curr=topo;curr!=NULL && curr->tag!=SCOPE;curr = topo->next)
  {
    if(strcmp(id, curr->val.pair.id)==0)
      return 1;
  }
  return 0;
}
