#!/bin/bash
TEMPFILE=../tmp
BUILDPATH=../build
SRCPATH=../src
if [ -r $SRCPATH/flex/monga_lexic.l ] && [ -s $SRCPATH/flex/monga_lexic.l ]
then
  #A fazer: importar essas variáveis de um arquivo de config
  #echo Construindo parser
  yacc --output=$TEMPFILE/tmp_grammatic.c --defines=$SRCPATH/main/definitions.h $SRCPATH/yacc/monga_grammar.y
  flex --outfile=$TEMPFILE/tmp_gen_expected.c --header-file=$SRCPATH/main/lex_defs.h $SRCPATH/flex/monga_lexic.l $SRCPATH/main/definitions.h

  #echo Building...
  if [ -z $1 ]
  then
    gcc -Wall -I$SRCPATH $SRCPATH/test/generate_expected.c $TEMPFILE/tmp_gen_expected.c $TEMPFILE/tmp_grammatic.c -o $SRCPATH/test/generate_expected -lfl
  else
    gcc -Wall -I$SRCPATH -D$1 $SRCPATH/test/generate_expected.c $TEMPFILE/tmp_gen_expected.c $TEMPFILE/tmp_grammatic.c -o $SRCPATH/test/generate_expected -lfl
  fi
  #echo Limpando tmp

  rm $TEMPFILE/tmp_grammatic.c
  rm $TEMPFILE/tmp_gen_expected.c
else
  echo Não tens permissão de leitura de monga_lexic.l ou está vazio
fi
