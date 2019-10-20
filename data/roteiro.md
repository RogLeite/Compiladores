#####Intro
--------------
- Como a última vez que programei em C puro foi em 2016.1 (em programação modular), eu efetivamente não me lembrava *como* programar em C, das _features_ que a linguagem me oferece nem de suas limitações.
- Portanto, não me senti nem capaz de planejar como o código deveria ficar, nem capaz de escrever um código *bom*, então me concentrei em entregar o que é pedido enquanto fazia um código capaz de ser facilmente alterado (vamos ver como isso deu certo com o _refactor_ da árvore) e alta densidade de commits no git para facilitar voltar à versões anteriores do código. O resultado dessa abordagem de *fazer sem pensar demais* pode ser vista na quantidade de arquivos no projeto. Regularmente limpo arquivos obsoletos.

#####Parte 1: O .c que chama tudo
-----------------------
Atualmente, o compilador consiste nos seguintes arquivos:
 - ast.c e seu header. O módulo que define e opera sobre a árvore de sintáxe abstrata.
 - var_table.c e seu header. O módulo da tabela de nomes e escopos, usado durante a costura da árvore.
 - monga_lexic.l. O arquivo flex com as definições léxicas de monga.
 - monga_grammar.y. O arquivo yacc com gramática de monga.
 - tree_stitcher.c. O arquivo com a main do compilador.
 tree_stitcher.c é quem chama `yyparse()` e as funções `printTree()`, `stitchTree()`, e `typeTree()`, todas do módulo ast.

#####Parte 2: ast.h Interface da Árvore
-------------


#####Parte 3: Como a gramática constrói a ast
-------------------


#####Parte 4: ast.c a Arvore de sintaxe abstrata
---------------------

#####Parte 5: var_table.h Interface da tabela de Identificadores
-------------------

#####Parte 6: Costura da Árvore
-------------------

#####Parte 7: var_table.c Implementação da tabela
-------------------

#####Parte 8: Tipagem da árvore
-------------------
