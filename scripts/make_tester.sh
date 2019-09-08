#!/bin/bash
TEMPFILE=/home/rodrigo/Documents/Compiladores/tmp
SRCPATH=/home/rodrigo/Documents/Compiladores/src
BUILDPATH=/home/rodrigo/Documents/Compiladores/build
SCRIPTSPATH=/home/rodrigo/Documents/Compiladores/scripts
if [ -r $SRCPATH/flex/monga_lexic.l ] && [ -s $SRCPATH/flex/monga_lexic.l ]
then
  #A fazer: importar essas variáveis de um arquivo de config
  flex --outfile=$TEMPFILE/tmp_tester.c $SRCPATH/flex/monga_lexic.l
  gcc -I$SRCPATH -D$1 $SRCPATH/test/tester.c $TEMPFILE/tmp_tester.c -o $SRCPATH/test/tester -lfl
  rm $TEMPFILE/tmp_tester.c
else
  echo Não tens permissão de leitura de monga_lexic.l ou está vazio
fi
