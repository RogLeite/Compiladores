
.PHONY := all clean

TMPPATH = tmp

SRCPATH = src

COMPILER = gcc
LINKER_FLAGS = -lfl
WARNING_FLAGS = -Wall #-fsanitize=address

INCLUDES = -I${SCRPATH}
#Faltam os defines
#DEFINES = -D${1}

OUT_NAME = monga_compiler
COMPILER_OUTPUT = -o ${OUT_NAME}


SRC = ${SRCPATH}/tree_stitcher.c
GRAMMAR = ${SRCPATH}/monga_grammar.y
TMP_GRAMMAR_HEADER = ${SRCPATH}/definitions.h

LEXIC = ${SRCPATH}/monga_lexic.y

TMP_GRAMMATIC = ${TMPPATH}/tmp_grammatic.c
TMP_LEXIC = ${TMPPATH}/tmp_lexic.c

C_FILES = ${SRC} ${TMP_GRAMMATIC} ${TMP_LEXIC} ${SRCPATH}/ast.c ${SRCPATH}/var_table.c

all: monga_compiler

monga_compiler: TMP_GRAMMATIC TMP_LEXIC
	@echo "Compilando compilador..."

TMP_GRAMMATIC:
	@echo "Compilando gramática..."
	yacc --output=${TMP_GRAMMATIC} --defines=${TMP_GRAMMAR_HEADER} ${GRAMMAR}

TMP_LEXIC:
	@echo "Compilando léxico..."

clean:
	@echo "Limpando"
	rm ${TMP_GRAMMATIC}
  #rm ${TMP_LEXIC}
