#!/bin/bash
TEMPFILE=/home/rodrigo/Documents/Compiladores/tmp
SRCPATH=/home/rodrigo/Documents/Compiladores/src
BUILDPATH=/home/rodrigo/Documents/Compiladores/build
SCRIPTSPATH=/home/rodrigo/Documents/Compiladores/scripts
DATAPATH=/home/rodrigo/Documents/Compiladores/data

cd $SCRIPTSPATH
./make_tester.sh TC_SIMPLEMAIN
cd $SRCPATH/test/
./tester < $DATAPATH/test_simple_main.mng

cd $SCRIPTSPATH
./make_tester.sh TC_FIB10
cd $SRCPATH/test/
./tester < $DATAPATH/test_fibonacci.mng

rm tester
