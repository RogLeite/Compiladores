#!/bin/bash
if [ -z $1 ]
then
  echo Não há argumentos suficientes
elif [ -r $1 ] && [ -s $1 ]
then
  echo Esse script é para compilar e rodar $1
  TEMPFILE=/home/rodrigo/Documents/Compiladores/tmp
  echo Construindo parser
  echo
  flex --outfile=$TEMPFILE/test_parser.c $1
  echo

  echo Building...
  echo
  gcc -o $TEMPFILE/test_parser_exe $TEMPFILE/test_parser.c -lfl
  echo


  echo Executando
  echo
  $TEMPFILE/test_parser_exe

fi
