#!/bin/bash
SRCPATH=../src
SCRIPTSPATH=scripts/
DATAPATH=../data

echo
echo TESTING GRAMMAR

cd $SCRIPTSPATH
if [[ -z $1 ]]; then
  ./make_grammatic_tester.sh
else
  ./make_grammatic_tester.sh $1
fi

cd $SRCPATH/
echo
echo Testando: test_simple_main.mng
./grammatic_tester < $DATAPATH/test_simple_main.mng

echo
echo Testando: test_fibonacci.mng
./grammatic_tester < $DATAPATH/test_fibonacci.mng

echo
echo Testando: ola_mundo.mng
./grammatic_tester < $DATAPATH/ola_mundo.mng

echo
echo Testando: simpler_main.mng
./grammatic_tester < $DATAPATH/simpler_main.mng

rm grammatic_tester
