#!/bin/bash
TEMPFILE=../tmp
SRCPATH=../src
if [ -r $SRCPATH/flex/monga_lexic.l ] && [ -s $SRCPATH/flex/monga_lexic.l ]
then
  #A fazer: importar essas variáveis de um arquivo de config
  yacc --output=$TEMPFILE/tmp_grammatic.c --defines=$SRCPATH/main/definitions.h $SRCPATH/yacc/monga_grammar.y
  flex --outfile=$TEMPFILE/tmp_lexic.c --header-file=$SRCPATH/main/lex_defs.h $SRCPATH/flex/monga_lexic.l $SRCPATH/main/definitions.h

  gcc -Wall -I$SRCPATH -D$1 $SRCPATH/test/lexic_tester.c $TEMPFILE/tmp_lexic.c $TEMPFILE/tmp_grammatic.c $SRCPATH/main/ast.c -o $SRCPATH/test/lexic_tester -lfl
  rm $TEMPFILE/tmp_tester.c
else
  echo Não tens permissão de leitura de monga_lexic.l ou está vazio
fi
