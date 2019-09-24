#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "main/definitions.h"

typedef union tree_node_t Node;

typedef enum node_tag_t{
  expression,
  block,
  declaracao,
  comando,
  tipo,
  variavel
} NodeTag;

typedef union tree_node_t{
  struct{
    NodeTag tag;
  } leaf;
  struct{
    NodeTag tag ;
    Node *e1;
  } uni;
  struct{
    NodeTag tag ;
    Node *e1,*e2;
  } bi;
  struct{
    NodeTag tag ;
    Node *e1,*e2,*e3;
  } tri;
} Node;

Node *global_tree;
/**
Como está no caderno
*/
//typedef struct exp_t Exp;
/*
typedef struct tree_node_t{
  NodeTag tag;
  union content_t{
    struct{ } leaf;
    struct{ Exp *e1; } uni;
    struct{ Exp *e1,*e2; } bi;
    struct{ Exp *e1,*e2,*e3; } tri;
  } content;
} Node;
*/

#endif
