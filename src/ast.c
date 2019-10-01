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
  "CTE_FLOATING",
  "CTE_INTEGER",
  "CTE_STRING",
  "LEAF",
  "UNI",
  "BI",
  "TRI",
  "ID_LEAF",
  "ID_UNI",
  "ID_BI",
  "ID_TRI"
};

char *tag_name[] = {
  "BLOCK",
  "BIBLOCK",
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
  "RETVAL",
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
  "FLOATING"
};


Node *mkCteIntegerNode(NodeTag tag, int val)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->cte_integer.tag = tag;
  newNode->cte_integer.n_type = CTE_INTEGER;
  newNode->cte_integer.value = val;
  return newNode;
}
Node *mkCteStringNode(NodeTag tag, char *val)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->cte_string.tag = tag;
  newNode->cte_string.n_type = CTE_STRING;
  newNode->cte_string.value = (char*)malloc(sizeof(char)*(strlen(val)+1));
  strcpy(newNode->cte_string.value, val);
  return newNode;
}
Node *mkCteFloatingNode(NodeTag tag, double val)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->cte_floating.tag = tag;
  newNode->cte_floating.n_type = CTE_FLOATING;
  newNode->cte_floating.value = val;
  return newNode;
}
Node *mkLeafNode(NodeTag tag)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->leaf.tag = tag;
  newNode->leaf.n_type = LEAF;
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
Node *mkIdLeafNode(NodeTag tag, char *id)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->id_leaf.tag = tag;
  newNode->id_leaf.n_type = ID_LEAF;
  newNode->id_leaf.id = (char*)malloc(sizeof(char)*(strlen(id)+1));
  strcpy(newNode->id_leaf.id, id);
  return newNode;
}
Node *mkIdUniNode(NodeTag tag, char *id, Node *first)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->id_uni.tag = tag;
  newNode->id_uni.n_type = ID_UNI;
  newNode->id_uni.id = (char*)malloc(sizeof(char)*(strlen(id)+1));
  strcpy(newNode->id_uni.id, id);
  newNode->id_uni.n1 = first;
  return newNode;
}
Node *mkIdBiNode(NodeTag tag, char *id, Node *first, Node *second)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->id_bi.tag = tag;
  newNode->id_bi.n_type = ID_BI;
  newNode->id_bi.id = (char*)malloc(sizeof(char)*(strlen(id)+1));
  strcpy(newNode->id_bi.id, id);
  newNode->id_bi.n1 = first;
  newNode->id_bi.n2 = second;
  return newNode;
}
Node *mkIdTriNode(NodeTag tag, char *id, Node *first, Node *second, Node *third)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->id_tri.tag = tag;
  newNode->id_tri.n_type = ID_TRI;
  newNode->id_tri.id = (char*)malloc(sizeof(char)*(strlen(id)+1));
  strcpy(newNode->id_tri.id, id);
  newNode->id_tri.n1 = first;
  newNode->id_tri.n2 = second;
  newNode->id_tri.n3 = third;
  return newNode;
}

Node *mkIntTypeNode()
{
  if(intType==NULL)
  {
    intType = (Node*)malloc(sizeof(Node));
    intType->leaf.tag = INTTYPE;
    intType->leaf.n_type = LEAF;
  }
  return intType;
}
Node *mkFloatTypeNode()
{
  if(floatType==NULL)
  {
    floatType = (Node*)malloc(sizeof(Node));
    floatType->leaf.tag = FLOATTYPE;
    floatType->leaf.n_type = LEAF;
  }
  return floatType;
}
Node *mkBoolTypeNode()
{
  if(boolType==NULL)
  {
    boolType = (Node*)malloc(sizeof(Node));
    boolType->leaf.tag = BOOLTYPE;
    boolType->leaf.n_type = LEAF;
  }
  return boolType;
}
Node *mkCharTypeNode()
{
  if(charType==NULL)
  {
    charType = (Node*)malloc(sizeof(Node));
    charType->leaf.tag = CHARTYPE;
    charType->leaf.n_type = LEAF;
  }
  return charType;
}
Node *mkTrueValueNode()
{
  if(trueValue==NULL)
  {
    trueValue = (Node*)malloc(sizeof(Node));
    trueValue->leaf.tag = TRUEVALUE;
    trueValue->leaf.n_type = LEAF;
  }
  return trueValue;
}
Node *mkFalseValueNode()
{
  if(falseValue==NULL)
  {
    falseValue = (Node*)malloc(sizeof(Node));
    falseValue->leaf.tag = FALSEVALUE;
    falseValue->leaf.n_type = LEAF;
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
  if(n==NULL)
    return;

  printf("\n");
  int i = 0;
  for (; i < identation-2;) {
    printf("| ");
    i++;
  }
  if (i<identation) {
    printf("\\_");
    i++;
  }
  //printf("__");
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
