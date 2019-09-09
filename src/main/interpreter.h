#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "main/definitions.h"

union node_t;
typedef union node_t Node;

typedef enum tree_tag_t{
  Eadd,
  Esub,
  Emul,
  Ediv,

} TreeTag;


/**
Como está no caderno
*/
typedef struct exp_t Exp;
typedef struct exp_t{
  TreeTag tag;
  union content_t{
    struct{ } leaf;
    struct{ Exp *e1; } uni;
    struct{ Exp *e1,*e2; } bi;
    struct{ Exp *e1,*e2,*e3; } tri;
  } content;
} Exp;

/**
Minha tentativa
*/
/*
typedef struct leaf_node_t{
  TreeTag tag;
} LeafNode;

typedef struct uni_node_t{
  TreeTag tag;
  Node* next;
} UniNode;

typedef struct bi_node_t{
  TreeTag tag;
  Node* e1;
  Node* e2;
} BiNode;

typedef union node_t{
  LeafNode leaf_node;
  UniNode uni_node;
  BiNode bi_node;
} Node;
*/





#endif
