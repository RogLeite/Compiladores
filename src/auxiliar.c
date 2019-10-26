/*
* Módulo de funções auxiliares
* Rodrigo Leite - 1413150 - 26/Outubro/2019
*
*
* Código de printerr e convert adaptado do site:
* http://www.firmcodes.com/write-printf-function-c/ (acesso 26/Outubro/2019 09:40)
*
**/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void printerr(char *msg,...); 				//Our printf function
char* convert(unsigned int, int); 		//Convert integer number into octal, hex, etc.

void* mymalloc(int size)
{
  void *newPtr = malloc(size);
  assert(newPtr != NULL);
  return newPtr;
}

void printerr(char* msg,...)
{
	char *traverse;
	unsigned int i;
	char *s;

	//Module 1: Initializing Myprintf's arguments
	va_list arg;
	va_start(arg, msg);

	for(traverse = msg; *traverse != '\0'; traverse++)
	{
		while( *traverse != '%' )
		{
			fputc(*traverse, stderr);
			traverse++;
		}

		traverse++;

		//Module 2: Fetching and executing arguments
		switch(*traverse)
		{
			case 'c' : i = va_arg(arg,int);		//Fetch char argument
						fputc(i, stderr);
						break;

			case 'd' : i = va_arg(arg,int); 		//Fetch Decimal/Integer argument
						if(i<0)
						{
							i = -i;
							fputc('-', stderr);
						}
						fputs(convert(i,10), stderr);
						break;

			case 'o': i = va_arg(arg,unsigned int); //Fetch Octal representation
						fputs(convert(i,8), stderr);
						break;

			case 's': s = va_arg(arg,char *); 		//Fetch string
						fputs(s, stderr);
						break;

			case 'x': i = va_arg(arg,unsigned int); //Fetch Hexadecimal representation
						fputs(convert(i,16), stderr);
						break;
		}
	}

	//Module 3: Closing argument list to necessary clean-up
	va_end(arg);
}

char *convert(unsigned int num, int base)
{
	static char Representation[]= "0123456789ABCDEF";
	static char buffer[50];
	char *ptr;

	ptr = &buffer[49];
	*ptr = '\0';

	do
	{
		*--ptr = Representation[num%base];
		num /= base;
	}while(num != 0);

	return(ptr);
}
