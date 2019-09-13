#!/bin/bash
SRCPATH=../src
SCRIPTSPATH=scripts/
DATAPATH=../../data

echo
echo TESTING GRAMMAR

cd $SCRIPTSPATH
./make_grammatic_tester.sh

cd $SRCPATH/test/
echo
echo Testando test_simple_main.mng
./grammatic_tester < $DATAPATH/test_simple_main.mng

echo
echo Testando test_fibonacci.mng
./grammatic_tester < $DATAPATH/test_fibonacci.mng

rm grammatic_tester
