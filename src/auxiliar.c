/*
* Módulo de funções auxiliares
* Rodrigo Leite - 1413150 - 26/Outubro/2019
**/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


void printerr(char *msg)
{
  fprintf(stderr, "%s\n", msg);
}

void* mymalloc(int size)
{
  void *newPtr = malloc(size);
  assert(newPtr != NULL);
  return newPtr;
}
