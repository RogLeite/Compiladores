#!/bin/bash
cd /home/rodrigo/Documents/Compiladores/tmp
while [ true ]
do
  read -p "Queres realmente limpar /tmp [y/n]? " RESPOSTA
  case $RESPOSTA in
    y)
      echo Limpando Temp
      rm -f *
      break
      ;;
    n)
      echo Cancelado
      break
      ;;
    *)
      echo Por favor digite \'y\' ou \'n\'
      ;;
  esac
done
