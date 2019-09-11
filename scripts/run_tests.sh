#!/bin/bash
SRCPATH=../src
SCRIPTSPATH=../../scripts
DATAPATH=../../data


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
