/*
* Árvore de Sintaxe Abstrata
* Rodrigo Leite - 1413150 - 07/Outubro/2019
**/
#define VERBOSE_CASTING 0
#include "ast.h"
#include "var_table.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define VALUE_POINTER_ADDRESS &(tree->content.pair.value)
#define SECOND_POINTER_ADDRESS &(tree->content.pair.value->content.pair.next)
#define THIRD_POINTER_ADDRESS &(tree->content.pair.value->content.pair.next->content.pair.next)

char *expandEscapes(char *src);
void setNextNode(Node *current, Node *next);

Node *getVardecType(Node *node);
char *getFuncdefId(Node *current);
Node *getFuncdefType(Node *node);





Node *getNextNode(Node *curr);
void setType(Node *node, Node *type);

int isNumericType(Node *type);
int isIntType(Node *type);
int isCharType(Node *type);
int isFloatType(Node *type);
int isBoolType(Node *type);
int isArrayType(Node *type);
Node *promoteIfIsChar(Node **node_ptr);
Node *promoteToChar(Node **node_ptr);
Node *promoteToInt(Node **node_ptr);
Node *promoteToFloat(Node **node_ptr);
int assignmentRule(Node **assignNodePtr, Node **expNodePtr);
int cmpType(Node *type1, Node *type2);
int cmpParamsTypes(Node *dec, Node *call);
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
"CHARACTER",
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
char *op_symbol[] = {
  "||",
  "&&",
  "==",
  "~=",
  "<=",
  ">=",
  "<",
  ">",
  "+",
  "-",
  "*",
  "/",
  "!",
  "-"
};

Node *mkCteIntegerNode(int val)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->tag = INTEGER;
  newNode->isGlobal = 0;
  newNode->temp = -1;
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
  newNode->isGlobal = 0;
  newNode->temp = -1;
  newNode->content.string = (char*)malloc(sizeof(char)*(strlen(val)+1));
  strcpy(newNode->content.string, val);
  newNode->reference = NULL;
  newNode->type = (tag==CHARACTER)?mkCharTypeNode():mkArrayTypeNode(mkCharTypeNode());
  newNode = mkUniNode(WRAPPER, newNode);
  return newNode;
}
Node *mkCteFloatingNode(double val)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->tag = FLOATING;
  newNode->isGlobal = 0;
  newNode->temp = -1;
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
    newNode->isGlobal = 0;
    newNode->temp = -1;
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
  newNode->isGlobal = 0;
  newNode->temp = -1;
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
  newNode->isGlobal = 0;
  newNode->temp = -1;
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
  newNode->isGlobal = 0;
  newNode->temp = -1;
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
  newNode->isGlobal = 0;
  newNode->temp = -1;
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
        case CHARACTER :
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
            printf("| Referencia: %s ", getNodeId(n->reference));
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

Node *ignoreWrapper(Node *node)
{
  if(node->tag!=WRAPPER)return node;
  return getValueNode(node);
}

Node *getValueNode(Node *curr)
{
  if(curr==NULL || curr->tag<WRAPPER)return NULL;
  return curr->content.pair.value;
}
Node *getSecondNode(Node *curr)
{
  if(curr==NULL || curr->tag<WRAPPER)return NULL;
  return getNextNode(getValueNode(curr));
}
Node *getThirdNode(Node *curr)
{
  if(curr==NULL || curr->tag<WRAPPER)return NULL;
  return getNextNode(getSecondNode(curr));
}
Node *getFourthNode(Node *curr)
{
  if(curr==NULL || curr->tag<WRAPPER)return NULL;
  return getNextNode(getThirdNode(curr));
}

Node *getNextNode(Node *curr)
{
  if(curr==NULL || (curr->tag<WRAPPER && curr->tag>=INTEGER))return NULL;
  return curr->content.pair.next;
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
    case CALL :
      idNode = getId(getNodeId(tree));
      if(idNode == NULL)
      {
        printf("Não foi encontrado um id\n");
        return -1;
      }
      tree->reference = idNode;
      //printf("Stitching: CALL (%s) \n", getNodeId(tree));
      if(getValueNode(tree) != NULL)
        if(stitchTree(getValueNode(tree))==-1) return -1;
      if(getNextNode(tree) != NULL)
        if(stitchTree(getNextNode(tree))==-1) return -1;
      break;
    case SIMPLEVAR :
      idNode = getId(getNodeId(tree));
      if(idNode == NULL)
      {
        printf("Não foi encontrado um id\n");
        return -1;
      }
      tree->reference = idNode;
      //printf("Stitching: SIMPLEVAR (%s) type:", getNodeId(tree));printType(getType(idNode));printf("\n");
      if(getNextNode(tree) != NULL)
        if(stitchTree(getNextNode(tree))==-1) return -1;
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
      if(newId(getNodeId(tree), tree)==-1)return -1;
      //printf("Stitching: %s (%s) type:", tag_name[tree->tag], getNodeId(tree));printType(getVardecType(tree));printf("\n");
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
  Info *newInfo;
  Node *newType, *type1, *type2;
  if(tree==NULL) return NULL;

  switch (tree->tag) {
    case INTTYPE :
    case BOOLTYPE :
    case FLOATTYPE :
    case CHARTYPE :
    case ARRAYTYPE :
      return tree;
    case TRUEVALUE :
    case FALSEVALUE :
    case INTEGER :
    case FLOATING :
    case STRING :
    case CHARACTER :
      return getType(tree);
      break;
    case EMPTY :
      setType(tree, NULL);
      return getType(tree);
      break;
    case SIMPLEVAR :
      //typeTree(getNextNode(tree), info);
      newType = getType(tree->reference);
      //printf("Typing: SIMPLEVAR (%s) type:", getNodeId(tree));printType(newType);printf("\n");
      setType(tree, newType);
      return getType(tree);
      break;
    case ARRAYVAR :
      type1 = typeTree(getValueNode(tree), info);
      type2 = typeTree(getSecondNode(tree), info);
      // printf("type1:");printType(type1);
      // printf("type2:");printType(type2);
      if(!isArrayType(type1))
      {
        printf("Tipagem: Indexação ilegal: %s não é um array\n",
                getNodeId(getValueNode(tree)->reference));
        setType(tree, NULL);
        return NULL;
      }
      type2 = promoteIfIsChar(SECOND_POINTER_ADDRESS);
      if(!isIntType(type2))
      {
       printf("Tipagem: Indexação ilegal da variavel %s: Tipo",
                getNodeId(getValueNode(tree)->reference));
       printType(type2);
       printf("não pode indexar um array\n");
       setType(tree, NULL);
       return NULL;
      }
      setType(tree, getValueNode(type1));
      return getType(tree);
      break;
    case OPERATION_UNARIA :
      type1 = typeTree(getSecondNode(tree), info);
      switch (ignoreWrapper(getValueNode(tree))->content.op) {
        case NOT:
          if(!isBoolType(type1))
          {
            printf("Tipagem: Operador ! não pode ser usado no tipo");
            printType(type1);
            printf("\n");
            setType(tree, NULL);
            return NULL;
          }
          setType(tree, type1);
          return getType(tree);
          break;
        case NEGATIVE:
          type1 = promoteIfIsChar(SECOND_POINTER_ADDRESS);
          if(!isNumericType(type1))
          {
            printf("Tipagem: Operador - não pode ser usado no tipo");
            printType(type1);
            printf("\n");
            setType(tree, NULL);
            return NULL;
          }
          setType(tree, type1);
          return getType(tree);
          break;
        default :
          setType(tree, NULL);
          return NULL;
          break;
      }
      break;
    case OPERATION_BINARIA :
      type1 = typeTree(getSecondNode(tree), info);
      type2 = typeTree(getThirdNode(tree), info);
      switch (ignoreWrapper(getValueNode(tree))->content.op)
      {
        case ADD :
        case SUBTRACT :
        case MULTIPLY :
        case DIVIDE :
          type1 = promoteIfIsChar(SECOND_POINTER_ADDRESS);
          type2 = promoteIfIsChar(THIRD_POINTER_ADDRESS);
          if(!isNumericType(type1))
          {
            printf("Tipagem: operador %s não pode ser usado com membro esquerdo do tipo", op_symbol[ignoreWrapper(getValueNode(tree))->content.op]);
            printType(type1);printf("\n");
            setType(tree, NULL);
            return NULL;
          }
          if(!isNumericType(type2))
          {
            printf("Tipagem: operador %s não pode ser usado com membro direito do tipo", op_symbol[ignoreWrapper(getValueNode(tree))->content.op]);
            printType(type2);printf("\n");
            setType(tree, NULL);
            return NULL;
          }
          if(isIntType(type1)&&cmpType(type1, type2))
          {
            setType(tree, type1);
            return getType(tree);
          }
          if(isFloatType(type1)&&cmpType(type1, type2))
          {
            setType(tree, type1);
            return getType(tree);
          }
          //Ultimo caso é que um deles é float o outro int
          //basta promover o int para float
          if(isIntType(type1))
            type1 = promoteToFloat(SECOND_POINTER_ADDRESS);
          if(isIntType(type2))
            type2 = promoteToFloat(THIRD_POINTER_ADDRESS);
          setType(tree, type1);
          return getType(tree);
          break;
        //Casos análogos aos aritméticos, mas tipam para bool
        case LESSOREQUAL :
        case GREATEROREQUAL :
        case LESS :
        case GREATER :
          type1 = promoteIfIsChar(SECOND_POINTER_ADDRESS);
          type2 = promoteIfIsChar(THIRD_POINTER_ADDRESS);
          if(!isNumericType(type1))
          {
            printf("Tipagem: operador %s não pode ser usado com membro esquerdo do tipo", op_symbol[ignoreWrapper(getValueNode(tree))->content.op]);
            printType(type1);printf("\n");
            setType(tree, NULL);
            return NULL;
          }
          if(!isNumericType(type2))
          {
            printf("Tipagem: operador %s não pode ser usado com membro direito do tipo", op_symbol[ignoreWrapper(getValueNode(tree))->content.op]);
            printType(type2);printf("\n");
            setType(tree, NULL);
            return NULL;
          }
          if((isIntType(type1)||isFloatType(type1))&&cmpType(type1, type2))
          {
            setType(tree, mkBoolTypeNode());
            return getType(tree);
          }
          //Ultimo caso é que um deles é float o outro int
          //basta promover o int para float
          if(isIntType(type1))
            type1 = promoteToFloat(SECOND_POINTER_ADDRESS);
          if(isIntType(type2))
            type2 = promoteToFloat(THIRD_POINTER_ADDRESS);
          setType(tree, mkBoolTypeNode());
          return getType(tree);
          break;
        case EQUAL :
        case NOTEQUAL :
          type1 = promoteIfIsChar(SECOND_POINTER_ADDRESS);
          type2 = promoteIfIsChar(THIRD_POINTER_ADDRESS);
          if( !isNumericType(type1) && !isBoolType(type1) )
          {
            printf("Tipagem: operador %s não pode ser usado com membro esquerdo do tipo", op_symbol[ignoreWrapper(getValueNode(tree))->content.op]);
            printType(type1);printf("\n");
            setType(tree, NULL);
            return NULL;
          }
          if( !isNumericType(type2) && !isBoolType(type2) )
          {
            printf("Tipagem: operador %s não pode ser usado com membro direito do tipo", op_symbol[ignoreWrapper(getValueNode(tree))->content.op]);
            printType(type2);printf("\n");
            setType(tree, NULL);
            return NULL;
          }
          if(cmpType(type1, type2))
          {
            setType(tree, mkBoolTypeNode());
            return getType(tree);
          }
          if(isFloatType(type1)&&isIntType(type2))
          {
            type2 = promoteToFloat(THIRD_POINTER_ADDRESS);
            setType(tree, mkBoolTypeNode());
            return getType(tree);
          }
          if(isIntType(type1)&&isFloatType(type2))
          {
            type1 = promoteToFloat(SECOND_POINTER_ADDRESS);
            setType(tree, mkBoolTypeNode());
            return getType(tree);
          }
          printf("Tipagem: operador %s não pode ser usado com a combinação de tipos:", op_symbol[ignoreWrapper(getValueNode(tree))->content.op]);
          printType(type1);printf("e");printType(type2);printf("\n");
          setType(tree, NULL);
          return getType(tree);
          break;
        case OR :
        case AND :
          if( !isBoolType(type1) )
          {
            printf("Tipagem: operador %s não pode ser usado com o tipo", op_symbol[ignoreWrapper(getValueNode(tree))->content.op]);
            printType(type1);printf("\n");
            setType(tree, NULL);
            return NULL;
          }
          if( !isBoolType(type2) )
          {
            printf("Tipagem: operador %s não pode ser usado com o tipo", op_symbol[ignoreWrapper(getValueNode(tree))->content.op]);
            printType(type2);printf("\n");
            setType(tree, NULL);
            return NULL;
          }

          setType(tree, mkBoolTypeNode());
          return getType(tree);
          break;
        default :
          setType(tree, NULL);
          return NULL;
          break;
      }
      break;
    case NEW :
      type1 = typeTree(getValueNode(tree), info);
      type2 = typeTree(getSecondNode(tree), info);
      type2 = promoteIfIsChar(SECOND_POINTER_ADDRESS);
      if(!isIntType(type2))
      {
       printf("Tipagem: Construção ilegal de array: Tipo");
       printType(type2);
       printf("não descreve um inteiro\n");
       setType(tree, NULL);
       //typeTree(getNextNode(tree), info);
       return getType(NULL);
      }
      setType(tree, mkArrayTypeNode(type1));
      //typeTree(getNextNode(tree), info);
      return getType(tree);
    case CAST :
      type1 = typeTree(getValueNode(tree), info);
      type2 = typeTree(getSecondNode(tree), info);
      setType(tree, type2);
      //typeTree(getNextNode(tree), info);
      return getType(tree);
      break;
    // case PRINT :
    //   type1 = typeTree(getValueNode(tree), info);
    //   setType(tree, NULL);
    //   return getType(tree);
    //   break;
    case IFELSE :
      typeTree(getThirdNode(tree), info);
    case IF :
    case WHILE :
      typeTree(getSecondNode(tree), info);
      type1 = typeTree(getValueNode(tree), info);
      if(!isBoolType(type1))
      {
         printf("Tipagem: Condição de um %s espera bool, é:", tag_name[tree->tag]);
         printType(type1);printf("\n");
         setType(tree, NULL);
         typeTree(getNextNode(tree), info);
         return getType(NULL);
      }
      setType(tree, NULL);
      typeTree(getNextNode(tree), info);
      return getType(NULL);
      break;
    case ASSIGN :
      type1 = typeTree(getValueNode(tree), info);
      type2 = typeTree(getSecondNode(tree), info);
      if(!assignmentRule(VALUE_POINTER_ADDRESS, SECOND_POINTER_ADDRESS))
      {
         printf("Tipagem: Atribuição ilegal de tipo");printType(type2);
         printf("para variável de tipo");printType(type1);
         printf("\n");
      }
      setType(tree, NULL);
      typeTree(getNextNode(tree), info);
      return getType(NULL);
      break;
    case FUNCDEF :
      typeTree(getSecondNode(tree), info);//Parametros
      type1 = typeTree(getThirdNode(tree), info); //Tipo

      newInfo = (Info*)malloc(sizeof(Info));
      newInfo->funcRetType = type1;
      typeTree(getFourthNode(tree), newInfo); //Bloco

      setType(tree, type1);
      typeTree(getNextNode(tree), info);
      return getType(tree);
      break;
    case RET :
      type1 = typeTree(getValueNode(tree), info);
      if(!cmpType(type1, info->funcRetType))
      {
        printf("Tipagem: Tipo do retorno (");printType(type1);
        printf(") incompatível com tipo da função (");printType(info->funcRetType);
        printf(")\n");
      }

      setType(tree, NULL);
      typeTree(getNextNode(tree), info);
      return getType(tree);
      break;
    // case PARAM :
    // case VARDEC :
    //   break;
    case CALL :
      typeTree(getSecondNode(tree), info);
      newType = getType(tree->reference);
      if(!cmpParamsTypes(getSecondNode(tree->reference), getSecondNode(tree)))
      {
        printf("Tipagem: Tipo dos parâmetros da chamada à função %s não casam com os de sua declaração\n",
                getFuncdefId(tree->reference));
      }
      setType(tree, newType);
      typeTree(getNextNode(tree), info);
      return getType(tree);
      break;
    case WRAPPER :
      newType = typeTree(getValueNode(tree), info);
      setType(tree, newType);
      typeTree(getNextNode(tree), info);
      return getType(tree);
      break;
    default :
      newType = typeTree(getValueNode(tree), info);
      setType(tree, NULL);
      typeTree(getNextNode(tree), info);
      return getType(tree);
      break;
  }

  return 0;
}

char *getNodeId(Node *node)
{
  Node *idNode;
  if(node->tag != VARDEC
    && node->tag != SIMPLEVAR
    && node->tag != PARAM
    && node->tag != CALL
    && node->tag != FUNCDEF) return NULL;
  idNode = ignoreWrapper(getValueNode(node));
  if(idNode==NULL)return NULL;
  return idNode->content.string;
}
Node *getVardecType(Node *node)
{
  if(node->tag != VARDEC && node->tag != PARAM) return NULL;
  return getSecondNode(node);
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
  return getThirdNode(node);
}

void setType(Node *node, Node *type)
{
  if(node!=NULL&&type!=NULL)
  {
    switch (type->tag) {
      case INTTYPE:
        node->type = mkIntTypeNode();
        break;
      case FLOATTYPE:
        node->type = mkFloatTypeNode();
        break;
      case CHARTYPE:
        node->type = mkCharTypeNode();
        break;
      case BOOLTYPE:
        node->type = mkBoolTypeNode();
        break;
      case ARRAYTYPE:
        node->type = mkArrayTypeNode(getValueNode(type));
        break;
      default :
        node->type = NULL;
    }
  }
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

int isNullType(Node *type)
{
  if(type==NULL)return 1;
  return (type->tag==EMPTY)?1:0;
}

int isNumericType(Node *type)
{
  if(type==NULL)return 0;
  return (isIntType(type) || isFloatType(type) || isCharType(type))?1:0;
}

int isIntType(Node *type)
{
  if(type==NULL)return 0;
  return (type->tag==INTTYPE)?1:0;
}

int isCharType(Node *type)
{
  if(type==NULL)return 0;
  return (type->tag==CHARTYPE)?1:0;
}

int isFloatType(Node *type)
{
  if(type==NULL)return 0;
  return (type->tag==FLOATTYPE)?1:0;
}

int isBoolType(Node *type)
{
  if(type==NULL)return 0;
  return (type->tag==BOOLTYPE)?1:0;
}

int isArrayType(Node *type)
{
  if(type==NULL)return 0;
  return (type->tag==ARRAYTYPE)?1:0;
}

Node *promoteIfIsChar(Node **node_ptr)
{
  if(isCharType(getType(*node_ptr)))
    return promoteToInt(node_ptr);
  return getType(*node_ptr);
}

Node *promoteToChar(Node **node_ptr)
{
  Node *exp_node = *node_ptr;
  //(*node_ptr)é o ponteiro para nó que trabalho normalmente
  if(node_ptr!=NULL&&(*node_ptr)!=NULL&&!isCharType(getType(*node_ptr)))
  {
    if(VERBOSE_CASTING==1)
    {
      printf("Tipagem:");
      printType(getType(*node_ptr));
      printf("promovido para char\n");
    }
    (*node_ptr) = mkBiNode(CAST, exp_node, mkCharTypeNode());
    setType((*node_ptr), mkCharTypeNode());
  }
  return getType(*node_ptr);
}

Node *promoteToInt(Node **node_ptr)
{
  Node *exp_node = *node_ptr;
  //(*node_ptr)é o ponteiro para nó que trabalho normalmente
  if(node_ptr!=NULL&&(*node_ptr)!=NULL&&!isIntType(getType(*node_ptr)))
  {
    if(VERBOSE_CASTING==1)
    {
      printf("Tipagem:");
      printType(getType(*node_ptr));
      printf("promovido para int\n");
    }
    (*node_ptr) = mkBiNode(CAST, exp_node, mkIntTypeNode());
    setType((*node_ptr), mkIntTypeNode());
  }
  return getType(*node_ptr);
}

Node *promoteToFloat(Node **node_ptr)
{
  Node *exp_node = *node_ptr;
  //(*node_ptr)é o ponteiro para nó que trabalho normalmente
  if(node_ptr!=NULL&&(*node_ptr)!=NULL&&!isFloatType(getType(*node_ptr)))
  {
    if(VERBOSE_CASTING==1)
    {
      printf("Tipagem:");
      printType(getType(*node_ptr));
      printf("promovido para float\n");
    }

    (*node_ptr) = mkBiNode(CAST, exp_node, mkFloatTypeNode());
    setType((*node_ptr), mkFloatTypeNode());
  }
  return getType(*node_ptr);
}

int assignmentRule(Node **assignNodePtr, Node **expNodePtr)
{
  if( assignNodePtr!=NULL && (*assignNodePtr)!=NULL
   && expNodePtr!=NULL && (*expNodePtr)!=NULL)
  {
    Node *assignType = getType(*assignNodePtr);
    Node *expType = getType(*expNodePtr);
    if(cmpType(assignType, expType))
    {
      return 1;
    }
    else if( isNumericType(assignType) && isNumericType(expType) )
    {
      if(isFloatType(assignType))
      {
        promoteToFloat(expNodePtr);
      }
      else if(isIntType(assignType))
      {
        promoteToInt(expNodePtr);
      }
      else if(isCharType(assignType))
      {
        promoteToChar(expNodePtr);
      }
      return 1;
    }
  }
  return 0;
}

int cmpType(Node *type1, Node *type2)
{
  if(type1==NULL && type2==NULL)
    return 1;
  else if(type1==NULL || type2==NULL)
    return 0;
  else if(isArrayType(type1) && isArrayType(type2))
    return cmpType(getValueNode(type1), getValueNode(type2));
  else
    return (type1->tag == type2->tag)?1:0;
}

int cmpParamsTypes(Node *dec, Node *call)
{
  if(dec==NULL && call==NULL)
    return 1;
  else if(dec==NULL || call==NULL)
    return 0;
  else if(dec->tag == PARAMLIST && call->tag == LISTEXP)
  {
    return cmpParamsTypes(getSecondNode(dec), getSecondNode(call))
            && cmpParamsTypes(getValueNode(dec), getValueNode(call));
  }
  else if(dec->tag == PARAMLIST || call->tag == LISTEXP)
  {
    return 0;
  }
  // printf("getType(dec):");printType(getType(dec));printf("\n");
  // printf("tag = %s | ", tag_name[call->tag]);
  // printf("getType(call):");printType(getType(call));printf("\n");
  return cmpType(getType(dec), getType(call));
}

void printType(Node *node) {
  if(node==NULL)
  {
    printf(" NULL ");
    return;
  }
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
