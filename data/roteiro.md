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
 - Node é a estrutura da árvore
 - NodeContent é o que diferencia os nós, se são folhas ou árvores.
 - Operators é o enum de operadores.
 - Cada tag é apenas um tipo de nó: folha, árvore unária, árvore binária, árvore ternária e árvore quaternária.
 - WRAPPER teve que ser definido para envolver as constantes, senão elas não se encaixavam na árvore de lisp (não poderiam ter um next).
 - As funções `mk*Node` servem para fazer um nó da árvore e, na sua construção, recebem os nós filhos.
 - Em retrospecto, acho que deveria ter diferenciado melhor os nós de comandos e expressões, especialmente para o caso de chamada de função;

#####Parte 3: Como a gramática constrói a ast
-------------------
 - No `start` seta a global_tree e caso seja `%empty` usa o `mkNullNode()`.
 - Quando se faz uma sub-árvore, passo a *TAG* dela.
 - Olhar para tipos: Array é a única exceção.
 - Olhar para a definição de constantes: Ainda tenho que corrigir o que é um `char`.

#####Parte 4: ast.c a Arvore de sintaxe abstrata
---------------------
 - Forward Declaration de diversas funções auxiliares.
 - Notar que, nas constantes, defino o tipo e aninho num WRAPPER.
 - Notar que os tipos são um uniNode sem filhos. Não deu para criar um nó para cada tipo apenas, porque não dava para usar o campo `next` do `Pair`.

#####Parte 5: var_table.h Interface da tabela de Identificadores
-------------------
 - É a interface sugerida pelo Roberto

#####Parte 6: var_table.c Implementação da tabela
-------------------
 - É uma pilha: a estrutura se chama Empilhável.
 - Empilhável tem a união Conteudo, a tag que diz qual dos campos do conteúdo se usa e ponteiro para o próximo.
 - Conteudo é um escopo ou o par Id e ponteiro para o nó dele.

#####Parte 7: Costura da Árvore
-------------------
 - Um grande switch
 - Em BLOCK e FUNCDEF entra em escopo, costura a sub-árvore e sai do escopo.
 - Em PARAM, VARDEC e FUNCDEF crio um novo Id n tabela.
 - Em CALL e SIMPLEVAR busco o Id na tabela.

#####Parte 8: Tipagem da árvore
-------------------
