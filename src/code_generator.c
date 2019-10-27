#include "ast.h"

int temporario = 0;
int newTemporario()
{
  return temporario++;
}
void printTemporario(int tmp)
{
    printf("a%d", tmp);
}
int printNewTemporario()
{
  int novo = newTemporario();
  printf("a%d", novo);
  return novo;
}

void generateTreeCode(Node *tree)
{

}
