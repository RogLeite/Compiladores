#ifndef AST_H
#define AST_H

typedef union tree_node_t Node;

typedef enum node_tag_t{
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
  PARAM,
  VARDECS,
  COMMANDS,
  IFELSE,
  IF,
  WHILE,
  ASSIGN,
  RETVAL,
  RET,
  PRINT,
  SIMPLEVAR,
  ARRAYVAR,
  OR,
  AND,
  EQUAL,
  NOTEQUAL,
  LESSOREQUAL,
  GREATEROREQUAL,
  LESS,
  GREATER,
  ADD,
  SUBTRACT,
  MULTIPLY,
  DIVIDE,
  CAST,
  NEW,
  NOT,
  NEGATIVE,
  CALL,
  LISTEXP,
  TRUE_VALUE,
  FALSE_VALUE,
  STRING,
  INTEGER,
  FLOATING
} NodeTag;

typedef union tree_node_t{
  struct{
    NodeTag tag;
    double value;
  } cte_floating;
  struct{
    NodeTag tag;
    int value;
  } cte_integer;
  struct{
    NodeTag tag;
    char *value;
  } cte_string;
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

Node *intType = NULL;
Node *floatType = NULL;
extern Node *boolType;
extern Node *charType;

extern Node *trueValue;
extern Node *falseValue;

Node *mkCteIntegerNode(NodeTag tag, int val);
Node *mkCteStringNode(NodeTag tag, char *val);
Node *mkCteFloatingNode(NodeTag tag, double val);

Node *mkLeafNode(NodeTag tag);
Node *mkUniNode(NodeTag tag, Node *first);
Node *mkBiNode(NodeTag tag, Node *first, Node *second);
Node *mkTriNode(NodeTag tag, Node *first, Node *second, Node *third);
Node *mkIdLeafNode(NodeTag tag, char *id);
Node *mkIdUniNode(NodeTag tag, char *id, Node *first);
Node *mkIdBiNode(NodeTag tag, char *id, Node *first, Node *second);
Node *mkIdTriNode(NodeTag tag, char *id, Node *first, Node *second, Node *third);

Node *mkIntTypeNode();
Node *mkFloatTypeNode();

#endif
