#!/bin/bash
TEMPFILE=../tmp
SRCPATH=../src
if [ -r $SRCPATH/monga_lexic.l ] && [ -s $SRCPATH/monga_lexic.l ]
then
  #A fazer: importar essas variáveis de um arquivo de config
  yacc --output=$TEMPFILE/tmp_grammatic.c --defines=$SRCPATH/definitions.h $SRCPATH/yacc/monga_grammar.y
  flex --outfile=$TEMPFILE/tmp_lexic.c --header-file=$SRCPATH/lex_defs.h $SRCPATH/monga_lexic.l $SRCPATH/definitions.h

  gcc -Wall -I$SRCPATH -D$1 $SRCPATH/lexic_tester.c $TEMPFILE/tmp_lexic.c $TEMPFILE/tmp_grammatic.c $SRCPATH/ast.c -o $SRCPATH/lexic_tester -lfl
  rm $TEMPFILE/tmp_tester.c
else
  echo Não tens permissão de leitura de monga_lexic.l ou está vazio
fi
