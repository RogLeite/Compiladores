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
char *getVarId(Node *current);
Node *getVardecType(Node *node);
char *getFuncdefId(Node *current);
Node *getFuncdefType(Node *node);
Node *ignoreWrapper(Node *node);
Node *getValueNode(Node *curr);
Node *getNextNode(Node *curr);
void setType(Node *node, Node *type);
Node *getType(Node *node);
int cmpType(Node *e1, Node *e2);
void printType(Node *node);
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
  newNode->reference = NULL;
  newNode->type = mkIntTypeNode();
  newNode = mkUniNode(WRAPPER, newNode);
  return newNode;
}
Node *mkCteStringNode(NodeTag tag, char *val)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->tag = tag;
  newNode->content.string = (char*)malloc(sizeof(char)*(strlen(val)+1));
  strcpy(newNode->content.string, val);
  newNode->reference = NULL;
  newNode->type = mkArrayTypeNode(mkCharTypeNode());
  newNode = mkUniNode(WRAPPER, newNode);
  return newNode;
}
Node *mkCteFloatingNode(double val)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->tag = FLOATING;
  newNode->content.d = val;
  newNode->reference = NULL;
  newNode->type = mkFloatTypeNode();
  newNode = mkUniNode(WRAPPER, newNode);
  return newNode;
}
Node *mkOperatorNode(Operators val)
{
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->tag = OPERATOR;
    newNode->content.op = val;
    newNode->reference = NULL;
    newNode->type = NULL;
    newNode = mkUniNode(WRAPPER, newNode);
    return newNode;
}
Node *mkNullNode()
{
  return mkUniNode(EMPTY, NULL);
}
Node *mkUniNode(NodeTag tag, Node *first)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->tag = tag;
  newNode->content.pair.value = first;
  newNode->reference = NULL;
  newNode->type = NULL;
  setNextNode(newNode, NULL);
  return newNode;
}
Node *mkBiNode(NodeTag tag, Node *first, Node *second)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->tag = tag;
  newNode->content.pair.value = first;
  newNode->reference = NULL;
  newNode->type = NULL;
  setNextNode(newNode, NULL);
  setNextNode(first, second);
  return newNode;
}
Node *mkTriNode(NodeTag tag, Node *first, Node *second, Node *third)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->tag = tag;
  newNode->content.pair.value = first;
  newNode->reference = NULL;
  newNode->type = NULL;
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
  newNode->reference = NULL;
  newNode->type = NULL;
  setNextNode(newNode, NULL);
  setNextNode(first, second);
  setNextNode(second, third);
  setNextNode(third, fourth);
  return newNode;
}

Node *mkIntTypeNode()
{
  return mkUniNode(INTTYPE, NULL);
}
Node *mkFloatTypeNode()
{
  return mkUniNode(FLOATTYPE, NULL);
}
Node *mkBoolTypeNode()
{
  return mkUniNode(BOOLTYPE, NULL);
}
Node *mkCharTypeNode()
{
  return mkUniNode(CHARTYPE, NULL);
}
Node *mkArrayTypeNode(Node *subtype)
{
  return mkUniNode(ARRAYTYPE, subtype);
}
Node *mkTrueValueNode()
{
  Node *newNode = mkUniNode(TRUEVALUE, NULL);
  newNode->type = mkBoolTypeNode();
  return newNode;
}
Node *mkFalseValueNode()
{
  Node *newNode = mkUniNode(FALSEVALUE, NULL);
  newNode->type = mkBoolTypeNode();
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
          if(getType(n)!=NULL)
          {
            printf("| Tipo:");
            printType(n->type);
          }
          if(n->content.pair.next != NULL)
          {
            printTree(n->content.pair.next, identation);
          }
          break;
        case FLOATING :
          printf("| Value: %f ", n->content.d);
          if(getType(n)!=NULL)
          {
            printf("| Tipo:");
            printType(n->type);
          }
          break;
        case INTEGER :
          printf("| Value: %d ", n->content.i);
          if(getType(n)!=NULL)
          {
            printf("| Tipo:");
            printType(n->type);
          }
          break;
        case STRING :
          tmp = expandEscapes(n->content.string);
          printf("| Value: \"%s\" ", tmp);
          free(tmp);
          if(getType(n)!=NULL)
          {
            printf("| Tipo:");
            printType(n->type);
          }
          break;
        case ID :
          tmp = expandEscapes(n->content.string);
          printf("| Value: \"%s\" ", tmp);
          free(tmp);
          break;
        case OPERATOR :
          printf("| Operator: %s ", op_name[n->content.op]);
          if(getType(n)!=NULL)
          {
            printf("| Tipo:");
            printType(n->type);
          }
          break;
        //UniNode
        default :
          if(n->reference!=NULL)
            printf("| Referencia: %s ", getVarId(n->reference));
          if(getType(n)!=NULL)
          {
            printf("| Tipo:");
            printType(getType(n));
          }
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
  char *id;
  Node *idNode;
  switch (tree->tag){
    case INTTYPE :
    case FLOATTYPE :
    case BOOLTYPE :
    case CHARTYPE :
    case TRUEVALUE :
    case FALSEVALUE :
    case EMPTY :
      if(getValueNode(tree) != NULL)
        {if(stitchTree(getValueNode(tree))==-1) return -1;}
      if(getNextNode(tree) != NULL)
        {if(stitchTree(getNextNode(tree))==-1) return -1;}
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

      break;
    case SIMPLEVAR :
      idNode = getId(getVarId(tree));
      if(idNode == NULL)
      {
        printf("Não foi encontrado um id\n");
        return -1;
      }
      tree->reference = idNode;
      break;
    case FUNCDEF :
      id = getFuncdefId(tree);
      if(newId(id, tree)==-1)return -1;

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
    case PARAM :
    case VARDEC :
      if(newId(getVarId(tree), tree)==-1)return -1;
      setType(tree, getVardecType(tree));
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

Node *typeTree(Node *tree, Info *info)
{
  Node *newType;
  if(tree==NULL) return NULL;//mkNullNode();

  switch (tree->tag) {
    case TRUEVALUE :
    case FALSEVALUE :
    case INTEGER :
    case FLOATING :
    case STRING :
      typeTree(getNextNode(tree), info);
      return getType(tree);
      break;
    case SIMPLEVAR :
      newType = getType(tree->reference);
      setType(tree, newType);
      typeTree(getNextNode(tree), info);
      return newType;
      break;
    default :
      newType = NULL;
      typeTree(getValueNode(tree), info);
      typeTree(getNextNode(tree), info);
      return newType;
      break;
  }

  return 0;
}

char *getVarId(Node *node)
{
  Node *idNode;
  if(node->tag != VARDEC && node->tag != SIMPLEVAR && node->tag != PARAM) return NULL;
  idNode = ignoreWrapper(getValueNode(node));
  if(idNode==NULL)return NULL;
  return idNode->content.string;
}
Node *getVardecType(Node *node)
{
  if(node->tag != VARDEC && node->tag != PARAM) return NULL;
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
  if(curr==NULL || (curr->tag<WRAPPER && curr->tag>=INTEGER))return NULL;
  return curr->content.pair.next;
}

void setType(Node *node, Node *type)
{
  if(node!=NULL)
    node->type = type;
}

Node *getType(Node *node)
{
  if(node!=NULL)
    return node->type;
  return NULL;
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

int cmpType(Node *e1, Node *e2)
{
  return 1;
}
void printType(Node *node) {
  if(node==NULL) return;
  switch (node->tag) {
    case INTTYPE:
      printf(" int ");
      break;
    case CHARTYPE:
      printf(" char ");
      break;
    case FLOATTYPE:
      printf(" float ");
      break;
    case BOOLTYPE:
      printf(" bool ");
      break;
    case ARRAYTYPE:
      printf(" [");
      printType(getValueNode(node));
      printf("] ");
    default :
      return;
  }
}
