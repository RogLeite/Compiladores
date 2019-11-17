/*
* Gerador de código para a árvore sintática
* Rodrigo Leite - 1413150 - 27/outubro/2019
**/
#include "ast.h"
#include <stdio.h>
#include <assert.h>


void codeGlobal(FILE *outfile);
void codeGlobalId(FILE *outfile, char *id);
void codeType(FILE *outfile, Node *typeTree);
void codeDefinitions(FILE *outfile, Node *tree);
void codeParamDefs(FILE *outfile, Node *tree);
void codeFuncDef(FILE *outfile, Node *tree);
void codeFuncBody(FILE *outfile, Node *tree);
void codeInBlock(FILE *outfile, Node *tree);
void codeCommands(FILE *outfile, Node *tree);
void codePrint(FILE *outfile, Node *tree);
void codeVardecGlobal(FILE *outfile, Node *tree);
void codeVardecLocal(FILE *outfile, Node *tree);
void codeAssignment(FILE *outfile, Node *tree);
void codeLeftRightTemps(FILE *oufile, int left, int right);
int codeZext(FILE *outfile, int oldTemp);
int codeExpression(FILE *outfile, Node *tree);

char *ll_intType = "i32";
char *ll_boolType = "i1";

int temporario = 0;
int newTemporario()
{
  return temporario++;
}

void resetTemporario()
{
  temporario = 0;
}

void codeTemporario(FILE *outfile, int tmp)
{
    fprintf(outfile, "%%a%d ", tmp);
}

int codeNewTemporario(FILE *outfile)
{
  int novo = newTemporario();
  fprintf(outfile, "%%a%d ", novo);
  return novo;
}

void codeGlobal(FILE *outfile)
{
  Node *tree = getGlobalTree();
  assert(tree != NULL);

  //Início para permitir printar coisas
  //string "%d"
  fprintf(outfile, "@percent_d = constant [3 x i8] c\"%%d\\00\"\n");
  //string "\n"
  fprintf(outfile, "@endl = constant [2 x i8] c\"\\0A\\00\"\n");
  fprintf(outfile,"declare %s @printf(i8*, ...)\n", ll_intType);

  switch (tree->tag) {
    case FUNCDEF:
      codeFuncDef(outfile, tree);
      break;
    case VARDEC:
      codeVardecGlobal(outfile, tree);
      break;
    case DEFS:
      codeDefinitions(outfile, tree);
      break;
    default:
      fprintf(outfile, "\t;case %s não implementado em codeGlobal()\n", tag_name[tree->tag]);
      break;
  }
  fprintf(outfile, "\n");
}

void codeGlobalId(FILE *outfile, char *id)
{
  fprintf(outfile, "@%s", id);
}

char *typeString(Node *typeTree)
{
  if(typeTree==NULL)
  {
    return "void";
  }
  else
  {
    switch (typeTree->tag) {
      case INTTYPE:
        return ll_intType;
        break;
      case FLOATTYPE:
        return ";FLOATTYPE não implementado em typeString()\n";
        break;
      case CHARTYPE:
        return ";CHARTYPE não implementado em typeString()\n";
        break;
      case BOOLTYPE:
        return ll_boolType;
        break;
      case ARRAYTYPE:
        return ";ARRAYTYPE não implementado em typeString()\n";
        break;
      default:
      {
        return ";Tipo desconhecido em typeString()\n";
      }
    }
  }
}

void codeType(FILE *outfile, Node *typeTree)
{
  fprintf(outfile, "%s ", typeString(typeTree));
}

void codeDefinitions(FILE *outfile, Node *tree)
{
  Node *first = getValueNode(tree);
  Node *second = getSecondNode(tree);

  //Primeiro nó filho
  switch (first->tag) {
    case FUNCDEF:
      codeFuncDef(outfile, first);
      break;
    case VARDEC:
      codeVardecGlobal(outfile, first);
      break;
    case DEFS:
      codeDefinitions(outfile, first);
      break;
    default:
      fprintf(outfile, "\t;case %s não implementado em codeDefinitions() para primeiro filho\n", tag_name[first->tag]);
      break;
  }

  //Segundo nó filho
  switch (second->tag) {
    case FUNCDEF:
      codeFuncDef(outfile, second);
      break;
    case VARDEC:
      codeVardecGlobal(outfile, second);
      break;
    default:
      fprintf(outfile, "\t;case %s não implementado em codeDefinitions() para segundo filho\n", tag_name[second->tag]);
      break;

  }

}

void codeParamDefs(FILE *outfile, Node *tree)
{
  switch(tree->tag)
  {
    case EMPTY:
      fprintf(outfile, "() ");
      break;
    default:
      fprintf(outfile, "\t;case %s não implementado em codeParamDefs()\n", tag_name[tree->tag]);
      break;
  }
}

void codeFuncDef(FILE *outfile, Node *tree)
{
  fprintf(outfile, "define %s ", typeString(getType(tree)));
  codeGlobalId(outfile, getNodeId(tree));
  codeParamDefs(outfile, getSecondNode(tree));
  codeFuncBody(outfile, tree);
}

void codeFuncBody(FILE *outfile, Node *tree)
{
  Node *in_block = getValueNode(getFourthNode(tree));

  resetTemporario();

  fprintf(outfile, "{\n");
  codeInBlock(outfile, in_block);
  fprintf(outfile, "\tret %s \n}\n", typeString(getType(tree)));

}

void codeInBlock(FILE *outfile, Node *tree)
{
  switch (tree->tag) {
    case EMPTY:
      fprintf(outfile, "\n");
      break;
    //Casos a serem repassados para codeCommands()
    case VARDEC:
    case VARDECS:
    case PRINT:
    case ASSIGN:
    case COMMANDS:
      codeCommands(outfile, tree);
      break;
    default:
      fprintf(outfile, "\t;case %s não implementado em codeInBlock()\n", tag_name[tree->tag]);
  }
}

void codeCommands(FILE *outfile, Node *tree)
{
  switch (tree->tag) {
    case PRINT:
      codePrint(outfile, tree);
      break;
    case ASSIGN:
      codeAssignment(outfile, tree);
      break;
    case COMMANDS:
      codeCommands(outfile, getValueNode(tree));
      codeCommands(outfile, getSecondNode(tree));
      break;
    case VARDECS:
      codeCommands(outfile, getValueNode(tree));
      codeCommands(outfile, getSecondNode(tree));
      break;
    case VARDEC:
      codeVardecLocal(outfile, tree);
      break;
    default:
      fprintf(outfile, "\t;case %s não implementado em codeCommands()\n", tag_name[tree->tag]);
  }
}

void codePrint(FILE *outfile, Node *tree)
{
  int temp = codeExpression(outfile, getValueNode(tree));
  //char *s =  typeString(getType(getValueNode(tree)));
  char *s =  ll_intType;
  fprintf(outfile, "\tcall %s (i8*, ...) @printf(i8* getelementptr ([3 x i8], [3 x i8]* @percent_d, %s 0, %s 0), %s ", s, s, s, s);
  codeTemporario(outfile, temp);
  fprintf(outfile, ")\n");
  fprintf(outfile, "\tcall %s (i8*, ...) @printf(i8* getelementptr ([2 x i8], [2 x i8]* @endl, %s 0, %s 0))\n", s, s, s);

}

void codeVardecGlobal(FILE *outfile, Node *tree)
{
  //@getNodeId(tree) = common global i32 0,
  codeGlobalId(outfile, getNodeId(tree));
  fprintf(outfile, " = common global %s 0\n", typeString(getType(tree)));
}

void codeVardecLocal(FILE *outfile, Node *tree)
{
  int temp = newTemporario();

  //%temp = alloca getType(tree)
  fprintf(outfile, "\t");
  codeTemporario(outfile, temp);
  fprintf(outfile, "= alloca %s\n", typeString(getType(tree)));

  //salvar o temporário no tree->temp
  setTemporario(tree, temp);
}

void codeAssignment(FILE *outfile, Node *tree)
{
  int exp_result = codeExpression(outfile, getSecondNode(tree));
  Node *varNode = getValueNode(tree);
  char *s = typeString(getType(varNode));
  //store getType(varNode) [exp], getType(varNode)* @getNodeId(varNode)/
  fprintf(outfile, "\tstore %s ", s);
  codeTemporario(outfile, exp_result);
  fprintf(outfile, ", %s* ", s);
  if(getReference(varNode)->isGlobal==1)
    codeGlobalId(outfile, getNodeId(varNode));
  else
    codeTemporario(outfile, getTemporario(getReference(varNode)));
  fprintf(outfile, "\n");
}

void codeLeftRightTemps(FILE *outfile, int left, int right)
{
  codeTemporario(outfile, left);
  fprintf(outfile, ", ");
  codeTemporario(outfile, right);
  fprintf(outfile, "\n");
}

int codeZext(FILE *outfile, int oldTemp)
{
  int tempNovo;
  fprintf(outfile, "\t");
  tempNovo = codeNewTemporario(outfile);
  fprintf(outfile, "= zext %s ", ll_boolType);
  codeTemporario(outfile, oldTemp);
  fprintf(outfile, " to %s\n", ll_intType);
  return tempNovo;
}

int codeExpression(FILE *outfile, Node *tree)
{
  tree = ignoreWrapper(tree);
  switch (tree->tag) {
    case INTEGER:
    {
      int temp1 = newTemporario();
      char *intString = typeString(getType(tree));
      //%temp1 = add i32 0, tree->content.i
      fprintf(outfile, "\t");
      codeTemporario(outfile, temp1);
      fprintf(outfile, " = add %s 0, %d\n", intString, tree->content.i);

      return temp1;
      break;
    }
    case SIMPLEVAR:
    {
      char *s = typeString(getType(tree));
      //%2 = load getType(tree), getType(tree)* @getNodeId(tree)
      fprintf(outfile, "\t");
      int temp1 = codeNewTemporario(outfile);
      fprintf(outfile, "= load %s, %s* ", s, s);

      if(getReference(tree)->isGlobal==1)
        codeGlobalId(outfile, getNodeId(tree));
      else
        codeTemporario(outfile, getTemporario(getReference(tree)));

      fprintf(outfile, "\n");
      return temp1;
      break;
    }
    case OPERATION_BINARIA:
    {
      char *s = typeString(getType(getSecondNode(tree)));
      Node *operatorNode = ignoreWrapper(getValueNode(tree));
      int tempLeftExp = codeExpression(outfile, getSecondNode(tree));
      int tempRightExp = codeExpression(outfile, getThirdNode(tree));

      //%tempNovo = add getTypeTree %tempLeftExp, %temRightExp
      fprintf(outfile, "\t");
      int tempNovo = codeNewTemporario(outfile);

      switch (operatorNode->content.op) {
        case ADD:
        {
          fprintf(outfile, "= add %s ", s);
          codeLeftRightTemps(outfile, tempLeftExp, tempRightExp);
          break;
        }
        case SUBTRACT:
        {
          fprintf(outfile, "= sub %s ", s);
          codeLeftRightTemps(outfile, tempLeftExp, tempRightExp);
          break;
        }
        case MULTIPLY:
        {
          fprintf(outfile, "= mul %s ", s);
          codeLeftRightTemps(outfile, tempLeftExp, tempRightExp);
          break;
        }
        case DIVIDE:
        {
          fprintf(outfile, "= sdiv %s ", s);
          codeLeftRightTemps(outfile, tempLeftExp, tempRightExp);
          break;
        }
        case LESS:
        {
          int oldTemp = tempNovo;
          fprintf(outfile, "= icmp slt %s ", s);
          codeLeftRightTemps(outfile, tempLeftExp, tempRightExp);
          tempNovo = codeZext(outfile, oldTemp);
          break;
        }
        case LESSOREQUAL:
        {
          int oldTemp = tempNovo;
          fprintf(outfile, "= icmp sle %s ", s);
          codeLeftRightTemps(outfile, tempLeftExp, tempRightExp);
          tempNovo = codeZext(outfile, oldTemp);
          break;
        }
        case GREATER:
        {
          int oldTemp = tempNovo;
          fprintf(outfile, "= icmp sgt %s ", s);
          codeLeftRightTemps(outfile, tempLeftExp, tempRightExp);
          tempNovo = codeZext(outfile, oldTemp);
          break;
        }
        default:
          fprintf(outfile, "\t;case %s não implementado em OPERATION_BINARIA em codeExpression()\n", op_name[operatorNode->content.op]);
      }

      return tempNovo;

      break;
    }
    case OPERATION_UNARIA:
    {
      char *s = typeString(getType(tree));
      Node *operatorNode = ignoreWrapper(getValueNode(tree));
      int tempExp = codeExpression(outfile, getSecondNode(tree));

      fprintf(outfile, "\t");
      int tempNovo = codeNewTemporario(outfile);

      switch (operatorNode->content.op) {
        case NEGATIVE:
        {
          //%tempNovo = mul getTypeTree -1, %tempExp
          fprintf(outfile, " = mul %s -1, ", s);
          codeTemporario(outfile, tempExp);
          break;
        }
        default:
          fprintf(outfile, "\t;case %s não implementado em OPERATION_UNARIA em codeExpression()\n", op_name[operatorNode->content.op]);
      }

      fprintf(outfile, "\n");

      return tempNovo;

      break;
    }
    default:
      fprintf(outfile, "\t;case %s não implementado em codeExpression()\n", tag_name[tree->tag]);
  }
  return -1;
}
