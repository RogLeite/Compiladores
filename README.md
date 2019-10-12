# Compilador de Monga
#### Rodrigo Leite da Silva - 1413150
#### 08/setembro/2019
=========================

Da pasta raiz você pode:
----------------------------------
 - Dar make no compilador, resultando no executável `monga_compiler`, e usá-lo num arquivo a tua escolha. O argumento PRINT_TREES do make.sh é opcional e permite ver a árvore sintática do programa compilado:
```
$ ./make.sh [PRINT_TREES]
$ ./monga_compiler < teu_programa_em_monga
```

 - Executar os testes léxicos:
```
$ ./lexic_tests.sh
```

 - Executar os testes gramaticais:
```
$ ./grammatic_tests.sh
```

 - Visualizar as árvores sintáticas dos testes
 ```
 $ ./grammatic_tests.sh PRINT_TREES
 ```
Obs.: As strings exibidas no valor dos nós da árvore(Value: ...) tiveram os caracteres escapados expandidos.

 - Não esqueça de verificar a permissão para execução. Caso não tenha, execute do diretório raiz:
```
$ chmod +x make.sh
$ chmod +x *_tests.sh
$ chmod +x scripts/make_*.sh
```
Exemplo de Árvore
-------------------------------
Essa é a árvore do programa ``` data/test_simple_main.mng ```
```
NodeTag: FUNCDEF
|____NodeTag: ID | Value: "main"
|____NodeTag: EMPTY
|____NodeTag: INTTYPE
|____NodeTag: BLOCK
| |____NodeTag: VARDECS
| | |____NodeTag: VARDEC
| | | |____NodeTag: ID | Value: "var"
| | | |____NodeTag: INTTYPE
| | |____NodeTag: COMMANDS
| | | |____NodeTag: ASSIGN
| | | | |____NodeTag: SIMPLEVAR
| | | | | |____NodeTag: ID | Value: "var"
| | | | |____NodeTag: INTEGER | Value: 0
| | | |____NodeTag: RET
| | | | |____NodeTag: SIMPLEVAR
| | | | | |____NodeTag: ID | Value: "var"
```
O programa consiste em apenas uma declaração de função, a ``` main ```, que define uma variável inteira ``` var ```, atribui a ela o valor ``` 0 ``` e retorna ```var```.
 - Os nós de tag ```EMPTY``` existem em lugares onde a gramática encontrou um ```%empty```. Sua primeira aparição na árvore acima indica que a função foi declarada como não recebendo parâmetros.


Arquivos Importantes
----------------------------
O arquivo em flex, com as definições léxicas de Monga é ``` src/monga_lexic.l ```

O arquivo em yacc, com as definições gramaticais de Monga é ``` src/monga_grammar.y ```

Os casos de teste estão na pasta ``` data/ ``` e os arquivos com extensão ```.mng``` estão na linguagem monga
Mas estão faltando os casos de erro:
 - Strings malformadas
 - Numeros errados

Vizualização de tokens
--------------------------
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
