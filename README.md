# Compilador de Monga
#### Rodrigo Leite da Silva - 1413150
#### 08/setembro/2019


#####Da pasta raiz você pode:
 - Para executar os testes léxicos:
```
$ ./lexic_tests.sh
```

 - Para executar os testes gramaticais:
```
$ ./grammatic_tests.sh
```

 - Para visualizar as árvores sintáticas do programa
 ```
 $ ./grammatic_tests.sh PRINT_TREES
 ```
Obs.: As strings exibidas no valor dos nós da árvore(Value: ...) tiveram os caracteres escapados expandidos
Dívida técnica: Tratar as áspas no início e final da string

 - Não esqueça de verificar a permissão para execução. Caso não tenha, execute: ``` chmod +x *_tests.sh ```

O arquivo em flex, com as definições léxicas de Monga estão no arquivo ``` src/flex/monga_lexic.l ```

O arquivo em yacc, com as definições gramaticais de Monga estão no arquivo ``` src/yacc/monga_grammar.y ```

Os casos de teste estão na pasta ``` data/ ``` e os arquivos com extensão ```.mng``` estão na linguagem monga
Mas estão faltando os casos de erro:
 - Strings malformadas
 - Numeros errados

Para visualisar os tokens dos arquivos de teste:
```
$ cd scripts/
$ ./view_tokens.sh
```
Obs.: Recomendo redirecionar o output para um arquivo de tua escolha, para melhorar a visualização
```
$ cd scripts/
$ ./view_tokens.sh >../tmp/tokens.txt
```
