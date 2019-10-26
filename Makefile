
.PHONY := all clean

TEMPFILE=tmp
SRCPATH=src

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

all: monga_compiler

monga_compiler: TMP_GRAMMATIC TMP_LEXIC
	@echo "Compilando compilador..."

TMP_GRAMMATIC:
	@echo "Compilando gramática..."

TMP_LEXIC:
	@echo "Compilando léxico..."

clean:
	@echo "Limpando..."
	rm tmp/file-*.txt
