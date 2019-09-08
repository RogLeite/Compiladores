# Compilador de Monga
#### Rodrigo Leite da Silva - 1413150
#### 08/setembro/2019

Para executar os testes léxicos:
```
$ cd scripts/
$ ./run_tests.sh
```
O arquivo em flex, com as definições léxicas de Monga estão no arquivo ``` src/flex/monga_lexic.l ```

Os casos de teste estão na pasta ``` data/ ```
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
