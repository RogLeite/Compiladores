#!/bin/bash
echo Esse script é para compilar rodar parser.l
PARSEDIR=/home/rodrigo/Documents/Compiladores/src/flex
TEMPFILE=/home/rodrigo/Documents/Compiladores/tmp
echo Parsedir é $PARSEDIR
cd $PARSEDIR
echo Construindo parser
echo
flex --outfile=$TEMPFILE/test_parser.c parser.l
echo

echo Building...
echo
gcc -o $TEMPFILE/test_parser_exe $TEMPFILE/test_parser.c -lfl
echo


echo Executando
echo
$TEMPFILE/test_parser_exe
