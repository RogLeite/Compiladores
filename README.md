# Compilador de Monga
#### Rodrigo Leite da Silva - 1413150
#### 08/setembro/2019
=========================

Da pasta raiz você pode:
----------------------------------
 - Dar make no compilador, resultando no executável `monga_compiler`, e usá-lo num arquivo a tua escolha. Ao ser executado, o .ll de `teu_programa_em_monga` será guardado em `Program.ll`:

```
$ make clean
$ make
$ ./monga_compiler < teu_programa_em_monga
```

 - Compilar `Program.ll` feito e executá-lo
```
$ make program
$ ./Program
```

Se quiser usar uma `main()` de um arquivo específico `file.c` use:
```
$ make SRC=file.c
```

Arquivos Importantes
----------------------------
O arquivo em flex, com as definições léxicas de Monga é ``` src/monga_lexic.l ```

O arquivo em yacc, com as definições gramaticais de Monga é ``` src/monga_grammar.y ```

#Monga
----------------
 - Atribuição à variáveis aceita as seguintes combinações de tipos:
 ```
 bool = bool;
 [tipo] = [tipo] #Com tipo==tipo
 float = float;
 float = int;
 float = char;
 int = int;
 int = float;
 int = char;
 char = char;
 char = float;
 char = int;
 ```

 - De código executável aceita: Declaração de variáveis globais e funções globais, essas funções não aceitam parâmetros nem tem tipo; o único tipo é `int`; atribuição a variáveis; o comando `@`.
