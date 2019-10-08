/*
* Árvore de Sintaxe Abstrata
* Rodrigo Leite - 1413150 - 07/Outubro/2019
**/
#ifndef AST_H
#define AST_H

typedef struct node_s Node;

typedef enum node_tag_t{
  INTTYPE = 0,//Leaf
  FLOATTYPE,//Leaf
  BOOLTYPE,//Leaf
  CHARTYPE,//Leaf
  TRUEVALUE,//Leaf
  FALSEVALUE,//Leaf
  INTEGER,//Uni wrapped Leaf
  FLOATING,//Uni wrapped Leaf
  STRING,//Uni wrapped Leaf
  ID,//Uni wrapped Leaf
  OPERATOR,//Uni wrapped Leaf
  WRAPPER,//Uni DEVE SEMPRE SER O PRIMEIRO UNI
  EMPTY,//Uni
  BLOCK,//Uni
  RET,//Uni
  PRINT,//Uni
  SIMPLEVAR,//Uni
  ARRAYTYPE,//Uni
  ARRAYVAR,//Bi
  CAST,//Bi
  NEW,//Bi
  CALL,//Bi
  LISTEXP,//Bi
  OPERATION_UNARIA,//Bi
  VARDEC,//Bi
  DEFS,//Bi
  PARAMLIST,//Bi
  PARAM,//Bi
  VARDECS,//Bi
  COMMANDS,//Bi
  IF,//Bi
  WHILE,//Bi
  ASSIGN,//Bi
  FUNCDEF,//Tri
  IFELSE,//Tri
  OPERATION_BINARIA, //Tri
  TYPEDFUNCDEF,//Quad
} NodeTag;

typedef enum ops_e{
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
  NOT,
  NEGATIVE,
}Operators;

typedef union content_u{
  char *string;
  int i;
  double d;
  Operators op;
  struct Pair{
    Node *value;
    Node *next;
  } pair;
} NodeContent;

typedef struct node_s{
    NodeTag tag;
    NodeContent content;
    //TODO Node *reference;
}Node;

extern Node *global_tree;

Node *mkCteIntegerNode(int val);
Node *mkCteStringNode(NodeTag tag, char *val);
Node *mkCteFloatingNode(double val);
Node *mkOperatorNode(Operators val);

//Serve para criar um nó que representa vazio, mas
//que mantenha a integridade da árvore
Node *mkNullNode();

Node *mkUniNode(NodeTag tag, Node *first);
Node *mkBiNode(NodeTag tag, Node *first, Node *second);
Node *mkTriNode(NodeTag tag, Node *first, Node *second, Node *third);
Node *mkQuadNode(NodeTag tag, Node *first, Node *second, Node *third, Node *fourth);

Node *mkIntTypeNode();
Node *mkFloatTypeNode();
Node *mkBoolTypeNode();
Node *mkCharTypeNode();

Node *mkTrueValueNode();
Node *mkFalseValueNode();

void setGlobalTree(Node *);
Node *getGlobalTree();

void printTree(Node *tree, int identation);
int stitchTree(Node *tree);

#endif
