#!/bin/bash
TEMPFILE=/home/rodrigo/Documents/Compiladores/tmp
BUILDPATH=/home/rodrigo/Documents/Compiladores/build
SRCPATH=/home/rodrigo/Documents/Compiladores/src
SCRIPTSPATH=/home/rodrigo/Documents/Compiladores/scripts
if [ -r $SRCPATH/flex/monga_lexer.l ] && [ -s $SRCPATH/flex/monga_lexer.l ]
then
  #A fazer: importar essas variáveis de um arquivo de config
  echo Construindo parser
  flex --outfile=$TEMPFILE/tmp_gen_expected.c $SRCPATH/flex/monga_lexer.l
  echo Building...
  gcc -I$SRCPATH $SRCPATH/test/generate_expected.c $TEMPFILE/tmp_gen_expected.c -o $SRCPATH/test/generate_expected -lfl
  echo Limpando tmp

  rm $TEMPFILE/tmp_gen_expected.c
else
  echo Não tens permissão de leitura de monga_lexer.l ou está vazio
fi
