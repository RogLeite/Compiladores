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
  INTEGER,//Uni wrapped Value
  FLOATING,//Uni wrapped Value
  STRING,//Uni wrapped Value
  CHARACTER,//Uni wrapped Value
  ID,//Uni wrapped Value
  OPERATOR,//Uni wrapped Value
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
  IFELSE,//Tri
  OPERATION_BINARIA, //Tri
  FUNCDEF,//Quad
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
    Node *reference; //Referência caso o nó seja um SIMPLEVAR ou CALL
    Node *type; //Tipo do nó, definido por typeTree() salvo o nó seja um tipo ou constante.
    int isGlobal;
    int temp;
}Node;

typedef struct info_s
{
  Node *funcRetType;
}Info;

extern Node *global_tree;
extern char *tag_name[];

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
Node *mkArrayTypeNode(Node *subtype);

Node *mkTrueValueNode();
Node *mkFalseValueNode();

void setGlobalTree(Node *);
Node *getGlobalTree();

char *getNodeId(Node *current);

Node *ignoreWrapper(Node *node);
Node *getValueNode(Node *curr);
Node *getSecondNode(Node *curr);
Node *getThirdNode(Node *curr);
Node *getFourthNode(Node *curr);

Node *getType(Node *node);

int isNullType(Node *type);
void setTemporario(Node *node, int temp);
int getTemporario(Node *node);
Node *getReference(Node *node);

void printTree(Node *tree, int identation);

/*Retorna -1 se houve erro de costura*/
int stitchTree(Node *tree);

/*Retorna o tipo da árvore*/
Node *typeTree(Node *tree, Info *info);

#endif
