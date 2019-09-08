#!/bin/bash

./make_generate_expected.sh READABLE=1
cd ../src/test/
echo
echo
echo Tokens do arquivo ../../data/test_lexic_tokens.txt
./generate_expected < ../../data/test_lexic_tokens.txt
echo
echo
echo Tokens do arquivo ../../data/test_simple_main.mng
./generate_expected < ../../data/test_simple_main.mng
echo
echo
echo Tokens do arquivo ../../data/test_fibonacci.mng
./generate_expected < ../../data/test_fibonacci.mng
echo
echo
rm generate_expected
