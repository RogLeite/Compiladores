#!/bin/bash

SRCPATH=../src
SCRIPTSPATH=../../scripts
DATAPATH=../../data
TEMPPATH=../../tmp

echo TESTING LEXIC
echo
cd scripts/
./make_generate_expected.sh READABLE=1

cd $SRCPATH/test/

./generate_expected < $DATAPATH/test_lexic_tokens.txt > $TEMPPATH/output.txt
echo Testando data/test_lexic_tokens.txt
if diff $TEMPPATH/output.txt expected/test_lexic_tokens.txt > /dev/null ; then
  echo Passou
else
  echo FALHOU Para mais detalhes:
  echo "./onde_falhou.sh test_lexic_tokens.txt"
fi
echo

./generate_expected < $DATAPATH/test_simple_main.mng > $TEMPPATH/output.txt
echo Testando data/test_simple_main.mng
if diff $TEMPPATH/output.txt expected/test_simple_main.mng > /dev/null ; then
  echo Passou
else
  echo FALHOU Para mais detalhes:
  echo "./onde_falhou.sh test_simple_main.mng"
fi
echo


./generate_expected < $DATAPATH/test_fibonacci.mng > $TEMPPATH/output.txt
echo Testando data/test_fibonacci.mng
if diff $TEMPPATH/output.txt expected/test_fibonacci.mng > /dev/null ; then
  echo Passou
else
  echo FALHOU Para mais detalhes:
  echo "./onde_falhou.sh test_fibonacci.mng"
fi
echo

rm generate_expected
rm $TEMPPATH/output.txt
