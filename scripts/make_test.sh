#!/bin/bash
TEMPFILE=/home/rodrigo/Documents/Compiladores/tmp
SRCPATH=/home/rodrigo/Documents/Compiladores/src
BUILDPATH=/home/rodrigo/Documents/Compiladores/build
SCRIPTSPATH=/home/rodrigo/Documents/Compiladores/scripts
if [ -r $SRCPATH/flex/monga_lexer.l ] && [ -s $SRCPATH/flex/monga_lexer.l ]
then
  #A fazer: importar essas variáveis de um arquivo de config
  echo Construindo parser
  flex --outfile=$TEMPFILE/tmp_tester.c $SRCPATH/flex/monga_lexer.l
  echo Building...
  gcc -I$SRCPATH $SRCPATH/test/tester.c $TEMPFILE/tmp_tester.c -o $SRCPATH/test/tester -lfl
  echo Limpando tmp

  rm $TEMPFILE/tmp_tester.c
else
  echo Não tens permissão de leitura de monga_lexer.l ou está vazio
fi
