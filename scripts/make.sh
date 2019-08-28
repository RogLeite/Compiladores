#!/bin/bash
if [ -z $1 ]
then
  echo Não há argumentos suficientes
elif [ -r $1 ] && [ -s $1 ]
then
  echo Esse script é para compilar e rodar $1
  TEMPFILE=/home/rodrigo/Documents/Compiladores/tmp
  SRCPATH=/home/rodrigo/Documents/Compiladores/src
  BUILDPATH=/home/rodrigo/Documents/Compiladores/build
  SCRIPTSPATH=/home/rodrigo/Documents/Compiladores/scripts
  #A fazer: importar essas variáveis de um arquivo de config
  echo Construindo parser
  echo
  flex --outfile=$TEMPFILE/monga_parser.c $1
  echo

  echo Building...
  echo
  gcc -I$SRCPATH  $TEMPFILE/monga_parser.c -o $BUILDPATH/monga_lexic -lfl

  echo
  rm $TEMPFILE/monga_parser.c
fi
