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
void codeCommand(FILE *outfile, Node *tree);

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
    fprintf(outfile, "%%a%d", tmp);
}

int printNewTemporario(FILE *outfile)
{
  int novo = newTemporario();
  fprintf(outfile, "%%a%d", novo);
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
  fprintf(outfile,"declare i32 @printf(i8*, ...)\n");

  switch (tree->tag) {
    case FUNCDEF:
      codeFuncDef(outfile, tree);
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
    case COMMANDS:
      codeInBlock(outfile, getValueNode(tree));
      codeCommand(outfile, getSecondNode(tree));
      break;
    default:
      fprintf(outfile, ";case %s não implementado em codeInBlock()\n", tag_name[tree->tag]);
  }
}

void codeCommand(FILE *outfile, Node *tree)
{
    fprintf(outfile, ";codeCommand() não implementado\n");
}
