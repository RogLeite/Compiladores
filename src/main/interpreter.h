#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "main/definitions.h"

typedef union tree_node_t Node;

typedef enum node_tag_t{
  expression,
  comando,
  tipo,
  variavel,
  BLOCK,
  VARDEC,
  DEFS,
  INTTYPE,
  FLOATTYPE,
  BOOLTYPE,
  CHARTYPE,
  ARRAYDEC,
  TYPEDFUNCDEF,
  FUNCDEF,
  PARAMLIST,
  PARAM
} NodeTag;

typedef union tree_node_t{
  struct{
    NodeTag tag;
  } leaf;
  struct{
    NodeTag tag ;
    Node *n1;
  } uni;
  struct{
    NodeTag tag ;
    Node *n1,*n2;
  } bi;
  struct{
    NodeTag tag ;
    Node *n1,*n2,*n3;
  } tri;
  struct{
    NodeTag tag;
    char *id;
  } id_leaf;
  struct{
    NodeTag tag;
    char *id;
    Node *n1;
  } id_uni;
  struct{
    NodeTag tag;
    char *id;
    Node *n1, *n2;
  } id_bi;
  struct{
    NodeTag tag;
    char *id;
    Node *n1, *n2, *n3;
  } id_tri;
} Node;

Node *global_tree;

Node *intType;
Node *floatType;
Node *boolType;
Node *charType;

/**
Como está no caderno
*/
//typedef struct exp_t Exp;
/*
typedef struct tree_node_t{
  NodeTag tag;
  union content_t{
    struct{ } leaf;
    struct{ Exp *n1; } uni;
    struct{ Exp *n1,*n2; } bi;
    struct{ Exp *n1,*n2,*n3; } tri;
  } content;
} Node;
*/

#endif
