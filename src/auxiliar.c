/*
* Módulo de funções auxiliares
* Rodrigo Leite - 1413150 - 26/Outubro/2019
**/
#include <stdio.h>
#include <stdlib.h>


void printerr(char *msg)
{
  fprintf(stderr, "%s\n", );
}

void* mymalloc(int size)
{
  void *newPtr = malloc(size);
  assert(newPtr != NULL);
  return newPtr;
}
