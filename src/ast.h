#ifndef AST_H
#define AST_H

typedef union tree_node_t Node;

typedef enum node_type_t{
  CTE_FLOATING = 0,
  CTE_INTEGER,
  CTE_STRING,
  LEAF,
  UNI,
  BI,
  TRI,
  ID_LEAF,
  ID_UNI,
  ID_BI,
  ID_TRI,
}NodeType;

typedef enum node_tag_t{
  BLOCK = 0, //
  BIBLOCK,
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
  TRUEVALUE,
  FALSEVALUE,
  STRING,
  INTEGER,
  FLOATING
} NodeTag;

typedef union tree_node_t{
  struct{
    NodeTag tag;
    NodeType n_type;
    double value;
  } cte_floating;
  struct{
    NodeTag tag;
    NodeType n_type;
    int value;
  } cte_integer;
  struct{
    NodeTag tag;
    NodeType n_type;
    char *value;
  } cte_string;
  struct{
    NodeTag tag;
    NodeType n_type;
  } leaf;
  struct{
    NodeTag tag;
    NodeType n_type;
    Node *n1;
  } uni;
  struct{
    NodeTag tag;
    NodeType n_type;
    Node *n1,*n2;
  } bi;
  struct{
    NodeTag tag;
    NodeType n_type;
    Node *n1,*n2,*n3;
  } tri;
  struct{
    NodeTag tag;
    NodeType n_type;
    char *id;
  } id_leaf;
  struct{
    NodeTag tag;
    NodeType n_type;
    char *id;
    Node *n1;
  } id_uni;
  struct{
    NodeTag tag;
    NodeType n_type;
    char *id;
    Node *n1, *n2;
  } id_bi;
  struct{
    NodeTag tag;
    NodeType n_type;
    char *id;
    Node *n1, *n2, *n3;
  } id_tri;
} Node;

extern Node *global_tree;

extern Node *intType;
extern Node *floatType;
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
Node *mkBoolTypeNode();
Node *mkCharTypeNode();

Node *mkTrueValueNode();
Node *mkFalseValueNode();

void setGlobalTree(Node *);
Node *getGlobalTree();

void printTree(Node *, int identation);

#endif
