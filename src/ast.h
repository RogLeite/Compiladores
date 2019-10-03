#ifndef AST_H
#define AST_H

typedef struct node_s Node;

typedef enum node_tag_t{
  BLOCK = 0,
  VARDEC,
  DEFS,
  INTTYPE,//Leaf
  FLOATTYPE,//Leaf
  BOOLTYPE,//Leaf
  CHARTYPE,//Leaf
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
  RET,//Uni
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
  TRUEVALUE,//Leaf
  FALSEVALUE,//Leaf
  STRING,//Leaf
  INTEGER,//Leaf
  FLOATING,//Leaf
  ID,//Leaf
} NodeTag;

enum ops_e{
  SYMBOL_OR,
  SYMBOL_AND,
  SYMBOL_EQUAL,
  SYMBOL_NOTEQUAL,
  SYMBOL_LESSOREQUAL,
  SYMBOL_GREATEROREQUAL,
  SYMBOL_LESS,
  SYMBOL_GREATER,
  SYMBOL_ADD,
  SYMBOL_SUBTRACT,
  SYMBOL_MULTIPLY,
  SYMBOL_DIVIDE,
  SYMBOL_NOT,
  SYMBOL_NEGATIVE,
};

typedef struct node_s{
    NodeTag tag;
    union content_u{
      char *string;
      int i;
      double d;
      enum ops_e op;
      struct Pair{
        Node *value;
        Node *next;
      } pair;
    }content;
}Node;

extern Node *global_tree;

extern Node *intType;
extern Node *floatType;
extern Node *boolType;
extern Node *charType;

extern Node *trueValue;
extern Node *falseValue;

Node *mkCteIntegerNode(int val);
Node *mkCteStringNode(char *val);
Node *mkCteFloatingNode(double val);

Node *mkIdNode(char *id);
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

void printTree(Node *, int identation);

#endif
