#include "ast.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char *expandEscapes(char *src);

Node *global_tree = NULL;

Node *intType = NULL;
Node *floatType = NULL;
Node *boolType = NULL;
Node *charType = NULL;

Node *trueValue = NULL;
Node *falseValue = NULL;

char *type_name[] = {
  "CONSTANT_DOUBLE",
  "CONSTANT_INTEGER",
  "CONSTANT_STRING",
  "LEAF",
  "ONE_CHILD",
  "TWO_CHILDREN",
  "THREE_CHILDREN",
  "WITH_ID_AND_LEAF",
  "WITH_ID_AND_ONE_CHILD",
  "WITH_ID_AND_TWO_CHILDREN",
  "WITH_ID_AND_THREE_CHILDREN"
};

char *tag_name[] = {
  "BLOCK",
  "VARDEC",
  "DEFS",
  "INTTYPE",
  "FLOATTYPE",
  "BOOLTYPE",
  "CHARTYPE",
  "ARRAYDEC",
  "TYPEDFUNCDEF",
  "FUNCDEF",
  "PARAMLIST",
  "PARAM",
  "VARDECS",
  "COMMANDS",
  "IFELSE",
  "IF",
  "WHILE",
  "ASSIGN",
  "RET",
  "PRINT",
  "SIMPLEVAR",
  "ARRAYVAR",
  "OR",
  "AND",
  "EQUAL",
  "NOTEQUAL",
  "LESSOREQUAL",
  "GREATEROREQUAL",
  "LESS",
  "GREATER",
  "ADD",
  "SUBTRACT",
  "MULTIPLY",
  "DIVIDE",
  "CAST",
  "NEW",
  "NOT",
  "NEGATIVE",
  "CALL",
  "LISTEXP",
  "TRUEVALUE",
  "FALSEVALUE",
  "STRING",
  "INTEGER",
  "FLOATING",
  "ID"
};


Node *mkCteIntegerNode(int val)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->tag = INTEGER;
  newNode->cte_integer.i = val;
  return newNode;
}
Node *mkCteStringNode(NodeTag tag, char *val)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->tag = tag;
  newNode->content.string = (char*)malloc(sizeof(char)*(strlen(val)+1));
  strcpy(newNode->content.string, val);
  return newNode;
}
Node *mkCteFloatingNode(double val)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->tag = CTE_FLOATING;
  newNode->content.d = val;
  return newNode;
}
Node *mkUniNode(NodeTag tag, Node *first)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->uni.tag = tag;
  newNode->uni.n_type = UNI;
  newNode->uni.n1 = first;
  return newNode;
}
Node *mkBiNode(NodeTag tag, Node *first, Node *second)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->bi.tag = tag;
  newNode->bi.n_type = BI;
  newNode->bi.n1 = first;
  newNode->bi.n2 = second;
  return newNode;
}
Node *mkTriNode(NodeTag tag, Node *first, Node *second, Node *third)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->tri.tag = tag;
  newNode->tri.n_type = TRI;
  newNode->tri.n1 = first;
  newNode->tri.n2 = second;
  newNode->tri.n3 = third;
  return newNode;
}

Node *mkQuadNode(NodeTag tag, Node *first, Node *second, Node *third, Node *fourth)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->tri.tag = tag;
  newNode->tri.n_type = TRI;
  newNode->tri.n1 = first;
  newNode->tri.n2 = second;
  newNode->tri.n3 = third;
  return newNode;
}

Node *mkIntTypeNode()
{
  if(intType==NULL)
  {
    intType = (Node*)malloc(sizeof(Node));
    intType->tag = INTTYPE;
  }
  return intType;
}
Node *mkFloatTypeNode()
{
  if(floatType==NULL)
  {
    floatType = (Node*)malloc(sizeof(Node));
    floatType->tag = FLOATTYPE;
  }
  return floatType;
}
Node *mkBoolTypeNode()
{
  if(boolType==NULL)
  {
    boolType = (Node*)malloc(sizeof(Node));
    boolType->tag = BOOLTYPE;
  }
  return boolType;
}
Node *mkCharTypeNode()
{
  if(charType==NULL)
  {
    charType = (Node*)malloc(sizeof(Node));
    charType->tag = CHARTYPE;
  }
  return charType;
}
Node *mkTrueValueNode()
{
  if(trueValue==NULL)
  {
    trueValue = (Node*)malloc(sizeof(Node));
    trueValue->tag = TRUEVALUE;
  }
  return trueValue;
}
Node *mkFalseValueNode()
{
  if(falseValue==NULL)
  {
    falseValue = (Node*)malloc(sizeof(Node));
    falseValue->tag = FALSEVALUE;
  }
  return falseValue;
}
void setGlobalTree(Node *tree)
{
  if (global_tree == NULL)
  {
    if(tree != NULL)
      global_tree = tree;
    else
      printf("tree é nula\n");
  }
}
Node *getGlobalTree()
{
  return global_tree;
}
void printTree(Node *n, int identation)
{
  // if(n==NULL)
  //   return;

  printf("\n");
  int i = 0;
  for (; i < identation-1;) {
    printf("| ");
    i++;
  }
  if (i<identation) {
    printf("|____");
    i++;
  }
  if (n==NULL)
  {
    printf("{vazio}");
  }
  else
  {
    printf("NodeType: %s | NodeTag: %s ", type_name[n->leaf.n_type], tag_name[n->leaf.tag]);
    char *tmp;
    switch(n->leaf.n_type){
      case CTE_FLOATING :
        printf("| Value: %f ", n->cte_floating.value);
        break;
      case CTE_INTEGER :
        printf("| Value: %d ", n->cte_integer.value);
        break;
      case CTE_STRING :
        tmp = expandEscapes(n->cte_string.value);
        printf("| Value: %s ", tmp);
        free(tmp);
        break;
      case ID_LEAF :
        tmp = expandEscapes(n->id_leaf.id);
        printf("| Id: %s", tmp);
        free(tmp);
        break;
      case LEAF :
        break;
      case ID_UNI :
        tmp = expandEscapes(n->id_uni.id);
        printf("| Id: %s", tmp);
        free(tmp);
        printTree(n->id_uni.n1, identation+1);
        break;
      case UNI :
        printTree(n->uni.n1, identation+1);
        break;
      case ID_BI :
        tmp = expandEscapes(n->id_bi.id);
        printf("| Id: %s", tmp);
        free(tmp);
        printTree(n->id_bi.n1, identation+1);
        printTree(n->id_bi.n2, identation+1);
        break;
      case BI :
        printTree(n->bi.n1, identation+1);
        printTree(n->bi.n2, identation+1);
        break;
      case ID_TRI :
        tmp = expandEscapes(n->id_tri.id);
        printf("| Id: %s", tmp);
        free(tmp);
        printTree(n->id_tri.n1, identation+1);
        printTree(n->id_tri.n2, identation+1);
        printTree(n->id_tri.n3, identation+1);
        break;
      case TRI :
        printTree(n->tri.n1, identation+1);
        printTree(n->tri.n2, identation+1);
        printTree(n->tri.n3, identation+1);
        break;
    }
  }
}
char *expandEscapes(char *src)
{
  char* str = (char*)malloc((strlen(src)*2+1)*sizeof(char));
  int i_str = 0;
  int i_src = 0;
  while(src[i_src] != '\0' || i_src<strlen(src))
  {
    if(src[i_src]== '\n'|| src[i_src]== '\t'|| src[i_src]== '\"'|| src[i_src]== '\\')
    {
      str[i_str] = '\\';
      i_str++;
      switch (src[i_src])
      {
        case '\n' :
          str[i_str] = 'n';
        break;
        case '\t' :
          str[i_str] = 't';
        break;
        case '\"' :
          str[i_str] = '\"';
        break;
        case '\\' :
          str[i_str] = '\\';
        break;
      }
    }
    else
    {
      str[i_str] = src[i_src];
    }
    i_src++;
    i_str++;
  }
  str[i_str] = '\0';
  return str;
}
