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
int codeExpression(FILE *outfile, Node *tree);

char *ll_intType = "i32";

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
      default:
      {
        return ";tipo não implementado em typeTree()\n";
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
  char *s =  typeString(getType(getValueNode(tree)));
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
  char *s = typeString(getType(getValueNode(tree)));
  //store getType(getValueNode(tree)) [exp], getType(getValueNode(tree))* @getNodeId(getValueNode(tree))
  fprintf(outfile, "\tstore %s ", s);
  codeTemporario(outfile, exp_result);
  fprintf(outfile, ", %s* ", s);
  codeGlobalId(outfile, getNodeId(getValueNode(tree)));
  fprintf(outfile, "\n");
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

      //Isso fica aqui em baixo para, talvez, ser reaproveitado
      // int temp2 = newTemporario();
      //
      // //%a1 = alloca i32
      // fprintf(outfile, "\t");
      // codeTemporario(outfile, temp1);
      // fprintf(outfile, " = alloca %s\n", intString);
      //
      // //store i32 tree->content.i, i32* %a1
      // fprintf(outfile, "\tstore %s %d, %s* ", intString, tree->content.i, intString);
      // codeTemporario(outfile, temp1);
      // fprintf(outfile, "\n");
      //
      // //%a2 = load i32, i32* %a1
      // fprintf(outfile, "\t");
      // codeTemporario(outfile, temp2);
      // fprintf(outfile, "= load %s, %s* ", intString, intString);
      // codeTemporario(outfile, temp1);
      // fprintf(outfile, "\n");

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
      //pegar a referência à declaração
      //verificar se é global
      //se não for global, imprimir o temporário
      codeGlobalId(outfile, getNodeId(tree));

      fprintf(outfile, "\n");
      return temp1;
      break;
    }
    default:
      fprintf(outfile, "\t;case %s não implementado em codeExpression()\n", tag_name[tree->tag]);
  }
  return -1;
}
