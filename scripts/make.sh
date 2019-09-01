#!/bin/bash
TEMPFILE=/home/rodrigo/Documents/Compiladores/tmp
SRCPATH=/home/rodrigo/Documents/Compiladores/src
BUILDPATH=/home/rodrigo/Documents/Compiladores/build
SCRIPTSPATH=/home/rodrigo/Documents/Compiladores/scripts
if [ -z $1 ] || [ -z $2 ]
then
  echo Não há argumentos suficientes
elif [ -r $SRCPATH/flex/$1 ] && [ -s $SRCPATH/flex/$1 ]
then
  echo Esse script é para compilar $1
  #A fazer: importar essas variáveis de um arquivo de config
  echo Construindo parser
  flex --outfile=$TEMPFILE/tmp_parser.c $SRCPATH/flex/$1
  echo Building...
  gcc -I$SRCPATH $SRCPATH/main/main.c $TEMPFILE/tmp_parser.c -o $BUILDPATH/$2 -lfl
  echo Limpando tmp

  rm $TEMPFILE/tmp_parser.c
else
  echo Não tens permissão de leitura de $1 ou está vazio
fi
