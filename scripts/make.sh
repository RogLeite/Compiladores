#!/bin/bash
if [ -z $1 ]
then
  echo Não há argumentos suficientes
elif [ -r $1 ] && [ -s $1 ]
then
  echo Esse script é para compilar $1
  TEMPFILE=/home/rodrigo/Documents/Compiladores/tmp
  SRCPATH=/home/rodrigo/Documents/Compiladores/src
  BUILDPATH=/home/rodrigo/Documents/Compiladores/build
  SCRIPTSPATH=/home/rodrigo/Documents/Compiladores/scripts
  #A fazer: importar essas variáveis de um arquivo de config
  echo Construindo parser
  flex --outfile=$TEMPFILE/tmp_parser.c $1
  echo Building...
  gcc -I$SRCPATH $SRCPATH/main/main.c $TEMPFILE/tmp_parser.c -o $BUILDPATH/monga_lexic -lfl
  echo Limpando tmp

  rm $TEMPFILE/tmp_parser.c
fi
