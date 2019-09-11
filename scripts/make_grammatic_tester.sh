#!/bin/bash
TEMPFILE=../tmp
SRCPATH=../src
if [ -r $SRCPATH/flex/monga_lexic.l ] && [ -s $SRCPATH/flex/monga_lexic.l ] && [ -r $SRCPATH/yacc/monga_grammar.y ] && [ -s $SRCPATH/yacc/monga_grammar.y ]
then
  #A fazer: importar essas variáveis de um arquivo de config
  yacc --output=$TEMPFILE/tmp_grammatic.c --defines=$SRCPATH/main/definitions.h $SRCPATH/yacc/monga_grammar.y
  flex --outfile=$TEMPFILE/tmp_lexic.c --header-file=$SRCPATH/main/lex_defs.h $SRCPATH/flex/monga_lexic.l $SRCPATH/main/definitions.h
  gcc -I$SRCPATH  $SRCPATH/test/grammar_tester.c $TEMPFILE/tmp_lexic.c $TEMPFILE/tmp_grammatic.c -o $SRCPATH/test/grammatic_tester -lfl
  rm $TEMPFILE/tmp_lexic.c
  rm $TEMPFILE/tmp_grammatic.c
else
  echo Não tens permissão de leitura de monga_lexic.l ou está vazio
fi
