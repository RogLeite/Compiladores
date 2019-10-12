/*
* Árvore de Sintaxe Abstrata
* Rodrigo Leite - 1413150 - 07/Outubro/2019
**/
#include "ast.h"
#include "var_table.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char *expandEscapes(char *src);
void setNextNode(Node *current, Node *next);
char *getVardecId(Node *current);
Node *getVardecType(Node *node);
char *getFuncdefId(Node *current);
Node *getFuncdefType(Node *node);
Node *ignoreWrapper(Node *node);
Node *getValueNode(Node *curr);
Node *getNextNode(Node *curr);

Node *global_tree = NULL;

char *tag_name[] = {
"INTTYPE" ,
"FLOATTYPE",
"BOOLTYPE",
"CHARTYPE",
"TRUEVALUE",
"FALSEVALUE",
"INTEGER",
"FLOATING",
"STRING",
"ID",
"OPERATOR",
"WRAPPER",
"EMPTY",
"BLOCK",
"RET",
"PRINT",
"SIMPLEVAR",
"ARRAYTYPE",
"ARRAYVAR",
"CAST",
"NEW",
"CALL",
"LISTEXP",
"OPERATION_UNARIA",
"VARDEC",
"DEFS",
"PARAMLIST",
"PARAM",
"VARDECS",
"COMMANDS",
"IF",
"WHILE",
"ASSIGN",
"IFELSE",
"OPERATION_BINARIA",
"FUNCDEF"
};

char *op_name[] = {
  "OR",               //"||",
  "AND",              //"&&",
  "EQUAL",            //"==",
  "NOTEQUAL",         //"~=",
  "LESSOREQUAL",      //"<=",
  "GREATEROREQUAL",   //">=",
  "LESS",             //"<",
  "GREATER",          //">",
  "ADD",              //"+",
  "SUBTRACT",         //"-",
  "MULTIPLY",         //"*",
  "DIVIDE",           //"/",
  "NOT",              //"!",
  "NEGATIVE"          //"-"
};

Node *mkCteIntegerNode(int val)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->tag = INTEGER;
  newNode->content.i = val;
  newNode = mkUniNode(WRAPPER, newNode);
  return newNode;
}
Node *mkCteStringNode(NodeTag tag, char *val)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->tag = tag;
  newNode->content.string = (char*)malloc(sizeof(char)*(strlen(val)+1));
  strcpy(newNode->content.string, val);
  newNode = mkUniNode(WRAPPER, newNode);
  return newNode;
}
Node *mkCteFloatingNode(double val)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->tag = FLOATING;
  newNode->content.d = val;
  newNode = mkUniNode(WRAPPER, newNode);
  return newNode;
}
Node *mkOperatorNode(Operators val)
{
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->tag = OPERATOR;
    newNode->content.op = val;
    newNode = mkUniNode(WRAPPER, newNode);
    return newNode;
}
Node *mkNullNode()
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->tag = EMPTY;
  newNode->content.pair.value = NULL;
  newNode->content.pair.next = NULL;
  return newNode;
}
Node *mkUniNode(NodeTag tag, Node *first)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->tag = tag;
  newNode->content.pair.value = first;
  newNode->content.pair.next = NULL;
  return newNode;
}
Node *mkBiNode(NodeTag tag, Node *first, Node *second)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->tag = tag;
  newNode->content.pair.value = first;
  setNextNode(newNode, NULL);
  setNextNode(first, second);
  return newNode;
}
Node *mkTriNode(NodeTag tag, Node *first, Node *second, Node *third)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->tag = tag;
  newNode->content.pair.value = first;
  setNextNode(newNode, NULL);
  setNextNode(first, second);
  setNextNode(second, third);
  return newNode;
}

Node *mkQuadNode(NodeTag tag, Node *first, Node *second, Node *third, Node *fourth)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->tag = tag;
  newNode->content.pair.value = first;
  setNextNode(newNode, NULL);
  setNextNode(first, second);
  setNextNode(second, third);
  setNextNode(third, fourth);
  return newNode;
}

Node *mkIntTypeNode()
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->tag = INTTYPE;
  newNode->content.pair.value = NULL;
  newNode->content.pair.next = NULL;
  return newNode;
}
Node *mkFloatTypeNode()
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->tag = FLOATTYPE;
  newNode->content.pair.value = NULL;
  newNode->content.pair.next = NULL;
  return newNode;
}
Node *mkBoolTypeNode()
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->tag = BOOLTYPE;
  newNode->content.pair.value = NULL;
  newNode->content.pair.next = NULL;
  return newNode;
}
Node *mkCharTypeNode()
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->tag = CHARTYPE;
  newNode->content.pair.value = NULL;
  newNode->content.pair.next = NULL;
  return newNode;
}
Node *mkTrueValueNode()
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->tag = TRUEVALUE;
  newNode->content.pair.value = NULL;
  newNode->content.pair.next = NULL;
  return newNode;
}
Node *mkFalseValueNode()
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->tag = FALSEVALUE;
  newNode->content.pair.value = NULL;
  newNode->content.pair.next = NULL;
  return newNode;
}
void setGlobalTree(Node *tree)
{
  if (global_tree == NULL)
  {
    if(tree == NULL)
      printf("global_tree foi setada como nula\n");
  }
  else
    printf("global_tree teve seu valor sobreescrito\n");
  global_tree = tree;
}
Node *getGlobalTree()
{
  return global_tree;
}

void setNextNode(Node *current, Node *next)
{
    current->content.pair.next = next;
}
void printTree(Node *n, int identation)
{
  if(n!=NULL && n->tag == WRAPPER)
  {
    printTree(n->content.pair.value, identation);
    if(n->content.pair.next != NULL)
      printTree(n->content.pair.next, identation);
  }
  else
  {
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
      char *tmp;
      printf("NodeTag: %s ", tag_name[n->tag]);
      switch(n->tag){
        case INTTYPE :
        case FLOATTYPE :
        case BOOLTYPE :
        case CHARTYPE :
        case TRUEVALUE :
        case FALSEVALUE :
        case EMPTY :
          if(n->content.pair.next != NULL)
            {
              printTree(n->content.pair.next, identation);
            }
          break;
        case FLOATING :
          printf("| Value: %f ", n->content.d);
          break;
        case INTEGER :
          printf("| Value: %d ", n->content.i);
          break;
        case STRING :
        case ID :
          tmp = expandEscapes(n->content.string);
          printf("| Value: \"%s\" ", tmp);
          free(tmp);
          break;
        case OPERATOR :
          printf("| Operator: %s ", op_name[n->content.op]);
          break;
        //UniNode
        default :
          printTree(n->content.pair.value, identation+1);
          if(n->content.pair.next != NULL)
            printTree(n->content.pair.next, identation);
          break;
      }
    }
  }
}

int stitchTree(Node *tree)
{
  switch (tree->tag){
    case INTTYPE :
    case FLOATTYPE :
    case BOOLTYPE :
    case CHARTYPE :
    case TRUEVALUE :
    case FALSEVALUE :
    case EMPTY :
      if(getNextNode(tree) != NULL)
        if(stitchTree(getNextNode(tree))==-1) return -1;
      break;
    case BLOCK :

      enterScope();

      if(getValueNode(tree) != NULL)
        if(stitchTree(getValueNode(tree))==-1) return -1;

      if(leaveScope()==-1)
      {
        printf("Erro, não há escopo para sair\n");
        return -1;
      }

      if(getNextNode(tree) != NULL)
        if(stitchTree(getNextNode(tree))==-1) return -1;

    case ARRAYVAR :
      break;
    case SIMPLEVAR :
      //TODO
      break;
    case FUNCDEF :
      if(newId(getFuncdefId(tree), tree)==-1)return -1;

      enterScope();
      if(getValueNode(tree) != NULL)
        if(stitchTree(getValueNode(tree))==-1) return -1;
      if(leaveScope()==-1)
      {
        printf("Erro, não há escopo para sair\n");
        return -1;
      }

      if(getNextNode(tree) != NULL)
        if(stitchTree(getNextNode(tree))==-1) return -1;

      break;
    case VARDEC :
      if(newId(getVardecId(tree), tree)==-1)return -1;
      if(getValueNode(tree) != NULL)
        if(stitchTree(getValueNode(tree))==-1) return -1;
      if(getNextNode(tree) != NULL)
        if(stitchTree(getNextNode(tree))==-1) return -1;
      break;
    default :
      if(getValueNode(tree) != NULL)
        if(stitchTree(getValueNode(tree))==-1) return -1;
      if(getNextNode(tree) != NULL)
        if(stitchTree(getNextNode(tree))==-1) return -1;
      break;
  }
  return 0;
}

char *getVardecId(Node *node)
{
  if(node->tag != VARDEC) return NULL;
  Node *idNode = ignoreWrapper(getValueNode(node));
  if(idNode==NULL)return NULL;
  return idNode->content.string;
}
Node *getVardecType(Node *node)
{
  if(node->tag != VARDEC) return NULL;
  return getNextNode(getValueNode(node));
}
char *getFuncdefId(Node *node)
{
  if(node->tag != FUNCDEF) return NULL;
  Node *idNode = ignoreWrapper(getValueNode(node));
  if(idNode==NULL)return NULL;
  return idNode->content.string;
}
Node *getFuncdefType(Node *node)
{
  if(node->tag != FUNCDEF) return NULL;
  return getNextNode(getNextNode(getValueNode(node)));
}

Node *ignoreWrapper(Node *node)
{
  if(node->tag!=WRAPPER)return NULL;
  return getValueNode(node);
}

Node *getValueNode(Node *curr)
{
  if(curr==NULL || curr->tag<WRAPPER)return NULL;
  return curr->content.pair.value;
}

Node *getNextNode(Node *curr)
{
  if(curr==NULL || curr->tag<WRAPPER)return NULL;
  return curr->content.pair.next;
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
