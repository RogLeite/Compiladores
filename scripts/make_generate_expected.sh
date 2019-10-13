#!/bin/bash
TEMPFILE=../tmp
BUILDPATH=../build
SRCPATH=../src
if [ -r $SRCPATH/monga_lexic.l ] && [ -s $SRCPATH/monga_lexic.l ]
then
  #A fazer: importar essas variáveis de um arquivo de config
  #echo Construindo parser
  yacc --output=$TEMPFILE/tmp_grammatic.c --defines=$SRCPATH/definitions.h $SRCPATH/monga_grammar.y
  flex --outfile=$TEMPFILE/tmp_gen_expected.c --header-file=$SRCPATH/lex_defs.h $SRCPATH/monga_lexic.l $SRCPATH/definitions.h

  #echo Building...
  if [ -z $1 ]
  then
    gcc -Wall -fsanitize=address -I$SRCPATH $SRCPATH/generate_expected.c $TEMPFILE/tmp_gen_expected.c $TEMPFILE/tmp_grammatic.c $SRCPATH/ast.c $SRCPATH/var_table.c -o $SRCPATH/generate_expected -lfl
  else
    gcc -Wall -fsanitize=address -I$SRCPATH -D$1 $SRCPATH/generate_expected.c $TEMPFILE/tmp_gen_expected.c $TEMPFILE/tmp_grammatic.c $SRCPATH/ast.c $SRCPATH/var_table.c -o $SRCPATH/generate_expected -lfl
  fi
  #echo Limpando tmp

  rm $TEMPFILE/tmp_grammatic.c
  rm $TEMPFILE/tmp_gen_expected.c
else
  echo Não tens permissão de leitura de monga_lexic.l ou está vazio
fi
