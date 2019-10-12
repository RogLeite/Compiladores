/*
* Tabela de Variáveis para costura da ast.h
* Rodrigo Leite - 1413150 - 07/Outubro/2019
**/
#include "var_table.h"
#include "ast.h"
#include <stdlib.h>
//#include <stdio.h>
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
  if (novo == NULL) {
    return -1;
  }
  novo->tag = SCOPE;
  novo->val.scope = scopeCounter;
  novo->next = NULL;
  scopeCounter++;
  //printf("\tEntrou %d\n", scopeCounter);
  push(novo);
  return scopeCounter;
}

int leaveScope()
{
  Empilhavel *curr;
  for(curr=pop();curr->tag!=SCOPE;curr = pop())
  {
    free(curr->val.pair.id);
    //printf("\tSaiu %d\n", scopeCounter);
    free(curr);
  }
  free(curr);
  scopeCounter--;
  return scopeCounter;
}

int newId(char *name, Node *node)
{
  Empilhavel *novo;

  if(name==NULL || isIdInScope(name)==1)
  {
    //printf("\t%s\n",(name == NULL?"nome == NULL":"Id in scope"));
    return -1;
  }

  novo = (Empilhavel*)malloc(sizeof(Empilhavel));
  if (novo == NULL) return -1;

  novo->tag = VAR;

  novo->val.pair.id = (char*)malloc(sizeof(char)*(strlen(name)+1));
  if (novo->val.pair.id == NULL) return -1;

  strcpy(novo->val.pair.id, name);
  novo->val.pair.node = node;
  novo->next = NULL;
  push(novo);
  return 0;
}

Node *getId(char *id)
{
  for(Empilhavel *curr=topo;curr!=NULL;curr = curr->next)
  {
    if(curr->tag==VAR && strcmp(id, curr->val.pair.id)==0)
      return curr->val.pair.node;
  }
  return NULL;
}

void push(Empilhavel *bloco)
{
  if(scopeCounter == 0)
    enterScope();
  bloco->next = topo;
  //printf("Pushed %s: %d on top of %d\n", (bloco->tag?"VAR":"SCOPE"), bloco, topo);
  topo = bloco;
}

Empilhavel *pop()
{
  Empilhavel *no = topo;
  if(topo==NULL)
    return NULL;
  topo = no->next;
  //printf("Popped %s: %d\n",(no->tag?"VAR":"SCOPE"), no);
  return no;
}

int isIdInScope(char *id)
{
  for(Empilhavel *curr=topo;((curr!=NULL) && (curr->tag!=SCOPE));curr = curr->next)
  {
    if(strcmp(id, curr->val.pair.id)==0)
    {
      return 1;
    }
  }
  return 0;
}
