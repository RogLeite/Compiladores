#!/bin/bash
SRCPATH=../src
SCRIPTSPATH=../../scripts
DATAPATH=../../data

echo TESTING LEXIC
echo
./make_lexic_tester.sh TC_LEXIC_TOKENS
cd $SRCPATH/test/
./lexic_tester < $DATAPATH/test_lexic_tokens.txt

cd $SCRIPTSPATH
./make_lexic_tester.sh TC_SIMPLEMAIN
cd $SRCPATH/test/
./lexic_tester < $DATAPATH/test_simple_main.mng

cd $SCRIPTSPATH
./make_lexic_tester.sh TC_FIB10
cd $SRCPATH/test/
./lexic_tester < $DATAPATH/test_fibonacci.mng

rm lexic_tester

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
