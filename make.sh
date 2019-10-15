#!/bin/bash
TEMPFILE=tmp
SRCPATH=src
if [ -r $SRCPATH/monga_lexic.l ] && [ -s $SRCPATH/monga_lexic.l ] && [ -r $SRCPATH/monga_grammar.y ] && [ -s $SRCPATH/monga_grammar.y ]
then
  #A fazer: importar essas variáveis de um arquivo de config
  yacc --output=$TEMPFILE/tmp_grammatic.c --defines=$SRCPATH/definitions.h $SRCPATH/monga_grammar.y
  flex --outfile=$TEMPFILE/tmp_lexic.c --header-file=$SRCPATH/lex_defs.h $SRCPATH/monga_lexic.l $SRCPATH/definitions.h
  if [[ -z $1 ]]; then
    gcc  -Wall -I$SRCPATH  $SRCPATH/tree_stitcher.c $TEMPFILE/tmp_lexic.c $TEMPFILE/tmp_grammatic.c $SRCPATH/ast.c $SRCPATH/var_table.c -o monga_compiler -lfl
    #gcc -fsanitize=address -Wall -I$SRCPATH  $SRCPATH/tree_stitcher.c $TEMPFILE/tmp_lexic.c $TEMPFILE/tmp_grammatic.c $SRCPATH/ast.c $SRCPATH/var_table.c -o monga_compiler -lfl
  else
    gcc  -Wall -D$1 -I$SRCPATH  $SRCPATH/tree_stitcher.c $TEMPFILE/tmp_lexic.c $TEMPFILE/tmp_grammatic.c $SRCPATH/ast.c $SRCPATH/var_table.c -o monga_compiler -lfl
    #gcc -fsanitize=address -Wall -D$1 -I$SRCPATH  $SRCPATH/tree_stitcher.c $TEMPFILE/tmp_lexic.c $TEMPFILE/tmp_grammatic.c $SRCPATH/ast.c $SRCPATH/var_table.c -o monga_compiler -lfl
  fi
  rm $TEMPFILE/tmp_lexic.c
  rm $TEMPFILE/tmp_grammatic.c
else
  echo Não tens permissão de leitura de monga_lexic.l ou está vazio
fi
