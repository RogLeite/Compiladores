#include "main/ast.h"
#include <string.h>
#include <stdlib.h>


Node *boolType = (Node*)malloc(sizeof(Node));
boolType->leaf.tag = BOOLTYPE;

Node *charType = (Node*)malloc(sizeof(Node));
charType->leaf.tag = CHARTYPE;

Node *trueValue = (Node*)malloc(sizeof(Node));
trueValue->leaf.tag = TRUE_VALUE;

Node *falseValue = (Node*)malloc(sizeof(Node));
falseValue->leaf.tag = FALSE_VALUE;

Node *mkCteIntegerNode(NodeTag tag, int val)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->cte_integer.tag = tag;
  newNode->cte_integer.value = val;
  return newNode;
}
Node *mkCteStringNode(NodeTag tag, char *val)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->cte_string.tag = tag;
  strcpy(newNode->cte_string.value, val);
  return newNode;
}
Node *mkCteFloatingNode(NodeTag tag, double val)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->cte_floating.tag = tag;
  newNode->cte_floating.value = val;
  return newNode;
}
Node *mkLeafNode(NodeTag tag)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->leaf.tag = tag;
  return newNode;
}
Node *mkUniNode(NodeTag tag, Node *first)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->uni.tag = tag;
  newNode->uni.n1 = first;
  return newNode;
}
Node *mkBiNode(NodeTag tag, Node *first, Node *second)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->bi.tag = tag;
  newNode->bi.n1 = first;
  newNode->bi.n2 = second;
  return newNode;
}
Node *mkTriNode(NodeTag tag, Node *first, Node *second, Node *third)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->tri.tag = tag;
  newNode->tri.n1 = first;
  newNode->tri.n2 = second;
  newNode->tri.n3 = third;
  return newNode;
}
Node *mkIdLeafNode(NodeTag tag, char *id)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  strcpy(newNode->id_leaf.id, id);
  newNode->id_leaf.tag = tag;
  return newNode;
}
Node *mkIdUniNode(NodeTag tag, char *id, Node *first)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->id_uni.tag = tag;
  strcpy(newNode->id_uni.id, id);
  newNode->id_uni.n1 = first;
  return newNode;
}
Node *mkIdBiNode(NodeTag tag, char *id, Node *first, Node *second)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->id_bi.tag = tag;
  strcpy(newNode->id_bi.id, id);
  newNode->id_bi.n1 = first;
  newNode->id_bi.n2 = second;
  return newNode;
}
Node *mkIdTriNode(NodeTag tag, char *id, Node *first, Node *second, Node *third)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->id_tri.tag = tag;
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
  }
  return intType;
}
Node *mkFloatTypeNode()
{
  if(floatType==NULL)
  {
    floatType = (Node*)malloc(sizeof(Node));
    floatType->leaf.tag = FLOATTYPE;
  }
  return floatType;
}
