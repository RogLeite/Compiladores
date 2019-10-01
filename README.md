# Compilador de Monga
#### Rodrigo Leite da Silva - 1413150
#### 08/setembro/2019
=========================

Da pasta raiz você pode:
----------------------------------
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
Obs.: As strings exibidas no valor dos nós da árvore(Value: ...) tiveram os caracteres escapados expandidos.

Dívida técnica: Tratar as áspas no início e final da string

 - Não esqueça de verificar a permissão para execução. Caso não tenha, execute do diretório raiz:
```
$ chmod +x *_tests.sh
$ chmod +x scripts/make_*.sh
```
Exemplo de Árvore
-------------------------------
Essa é a árvore do programa ``` data/test_simple_main.mng ```
```
NodeType: WITH_ID_AND_THREE_CHILDREN | NodeTag: TYPEDFUNCDEF | Id: main
|____{vazio}
|____NodeType: LEAF | NodeTag: INTTYPE
|____NodeType: ONE_CHILD | NodeTag: BLOCK
| |____NodeType: TWO_CHILDREN | NodeTag: VARDECS
| | |____NodeType: WITH_ID_AND_ONE_CHILD | NodeTag: VARDEC | Id: var
| | | |____NodeType: LEAF | NodeTag: INTTYPE
| | |____NodeType: TWO_CHILDREN | NodeTag: COMMANDS
| | | |____NodeType: TWO_CHILDREN | NodeTag: ASSIGN
| | | | |____NodeType: WITH_ID_AND_LEAF | NodeTag: SIMPLEVAR | Id: var
| | | | |____NodeType: CONSTANT_INTEGER | NodeTag: INTEGER | Value: 0
| | | |____NodeType: ONE_CHILD | NodeTag: RETVAL
| | | | |____NodeType: WITH_ID_AND_LEAF | NodeTag: SIMPLEVAR | Id: var

```
O programa consiste em apenas uma declaração de função, a ``` main ```, que define uma variável inteira ``` var ```, atribui a ela o valor ``` 0 ``` e retorna ```var```.
 - A árvore começa com a linha ```NodeType: WITH_ID_AND_THREE_CHILDREN | NodeTag: TYPEDFUNCDEF | Id: main``` que é sua raiz. Quando o nó tem o campo ```NodeType``` com um valor que começa com "```WITH_ID```", esse identificador será visível no próprio nó, no campo ```Id```. Então, pela ```NodeTag```, vemos que esse primeiro nó corresponde a uma definição de função que retornará algum valor, tem um identificador correspondente ```main``` e três filhos, denotados por ```|____```:
 - O primeiro filho é: ```{vazio}```. Como a ```main``` foi declarada sem ter parâmetros, o nó filho que corresponderia a lista de parâmetros não existe.
 - O segundo filho é ```NodeType: LEAF | NodeTag: INTTYPE```. Esse nó não tem filhos próprios pois o ```NodeType``` é ```LEAF``` e, pela ```NodeTag```, corresponde ao tipo inteiro da linguagem.
 - O terceiro filho é ```NodeType: ONE_CHILD | NodeTag: BLOCK```. Não tem identificador correspondente por ser um Bloco, e tem apenas um filho, denotado por ```| |____```.
 - Esse filho do bloco (e neto da raiz) é o nó: ```NodeType: TWO_CHILDREN | NodeTag: VARDECS```. É a declaração de variáveis, com dois filhos, denotados por ```| | |____```. O primeiro, ```NodeType: WITH_ID_AND_ONE_CHILD | NodeTag: VARDEC | Id: var```, é uma declaração e tem um filho, o tipo da variável. O segundo é a continuação, que pode ser outra declaração de variáveis ou, como nesse caso, uma série de comandos (```NodeType: TWO_CHILDREN | NodeTag: COMMANDS```). 

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
