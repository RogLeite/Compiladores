#!/bin/bash

SRCPATH=../src
SCRIPTSPATH=../scripts
DATAPATH=../data
TEMPPATH=../tmp


cd scripts/
./make_generate_expected.sh READABLE=1

cd $SRCPATH/

./generate_expected < $DATAPATH/$1 > $TEMPPATH/output.txt
cmp $TEMPPATH/output.txt expected/$1
rm $TEMPPATH/output.txt
rm generate_expected
