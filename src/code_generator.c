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
int codeExpression(FILE *outfile, Node *tree);

const char *ll_intType = "i32";

int temporario = 0;
int newTemporario()
{
  return temporario++;
}

void resetTemporario()
{
  temporario = 0;
}

void printTemporario(FILE *outfile, int tmp)
{
    fprintf(outfile, "%%a%d ", tmp);
}

int printNewTemporario(FILE *outfile)
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
      fprintf(outfile, ";case %s não implementado em codeGlobal()\n", tag_name[tree->tag]);
      break;
  }
  fprintf(outfile, "\n");
}

void codeGlobalId(FILE *outfile, char *id)
{
  fprintf(outfile, "@%s", id);
}

void codeType(FILE *outfile, Node *typeTree)
{
  if(typeTree==NULL)
  {
    fprintf(outfile, "void ");
  }
  else
  {
    switch (typeTree->tag) {
      case INTTYPE:
        fprintf(outfile, "%s", ll_intType);
        break;
      default:
        fprintf(outfile, ";case %s não implementado em codeType()\n", tag_name[typeTree->tag]);
    }
  }
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
      fprintf(outfile, ";case %s não implementado em codeDefinitions() para primeiro filho\n", tag_name[first->tag]);
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
      fprintf(outfile, ";case %s não implementado em codeDefinitions() para segundo filho\n", tag_name[second->tag]);
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
      fprintf(outfile, ";case %s não implementado em codeParamDefs()\n", tag_name[tree->tag]);
      break;
  }
}

void codeFuncDef(FILE *outfile, Node *tree)
{
  fprintf(outfile, "define ");
  codeType(outfile, getType(tree));
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
  fprintf(outfile, "\tret ");
  codeType(outfile, getType(tree));
  fprintf(outfile, "\n}\n");

}

void codeInBlock(FILE *outfile, Node *tree)
{
  switch (tree->tag) {
    case EMPTY:
      fprintf(outfile, "\n");
      break;
    //Casos a serem repassados para codeCommands()
    case PRINT:
      codeCommands(outfile, tree);
      break;
    case COMMANDS:
      codeCommands(outfile, tree);
      break;
    default:
      fprintf(outfile, ";case %s não implementado em codeInBlock()\n", tag_name[tree->tag]);
  }
}

void codeCommands(FILE *outfile, Node *tree)
{
  switch (tree->tag) {
    case PRINT:
      codePrint(outfile, tree);
      break;
    case COMMANDS:
      codeCommands(outfile, getValueNode(tree));
      codeCommands(outfile, getSecondNode(tree));
    default:
      fprintf(outfile, ";case %s não implementado em codeCommands()\n", tag_name[tree->tag]);
  }
}

void codePrint(FILE *outfile, Node *tree)
{
  int temp = codeExpression(outfile, getValueNode(tree));
  fprintf(outfile, "\tcall %s (i8*, ...) @printf(i8* getelementptr ([3 x i8], [3 x i8]* @percent_d, %s 0, %s 0), %s ", ll_intType, ll_intType, ll_intType, ll_intType);
  printTemporario(outfile, temp);
  fprintf(outfile, ")\n");
  fprintf(outfile, "\tcall %s (i8*, ...) @printf(i8* getelementptr ([2 x i8], [2 x i8]* @endl, %s 0, %s 0))\n", ll_intType, ll_intType, ll_intType);

}

void codeVardecGlobal(FILE *outfile, Node *tree)
{
  //@getNodeId(tree) = common global i32 0,
  codeGlobalId(outfile, getNodeId(tree));
  fprintf(outfile, " = common global ");
  codeType(outfile, getType(tree));
  fprintf(outfile, " 0\n");
}

int codeExpression(FILE *outfile, Node *tree)
{
  tree = ignoreWrapper(tree);
  switch (tree->tag) {
    case INTEGER:
    {
      int temp1 = newTemporario();
      int temp2 = newTemporario();

      //%a1 = alloca i32
      fprintf(outfile, "\t");
      printTemporario(outfile, temp1);
      fprintf(outfile, " = alloca %s\n", ll_intType);

      //store i32 tree->content.i, i32* %a1
      fprintf(outfile, "\tstore %s %d, %s* ", ll_intType, tree->content.i, ll_intType);
      printTemporario(outfile, temp1);
      fprintf(outfile, "\n");

      //%a2 = load i32, i32* %a1
      fprintf(outfile, "\t");
      printTemporario(outfile, temp2);
      fprintf(outfile, "= load %s, %s* ", ll_intType, ll_intType);
      printTemporario(outfile, temp1);
      fprintf(outfile, "\n");
      return temp2;
      break;
    }
    default:
      fprintf(outfile, ";case %s não implementado em codeExpression()\n", tag_name[tree->tag]);
  }
  return 0;
}
