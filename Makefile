#
# Makefile do compilador de Monga
# Rodrigo Leite - 1413150 - 26/outubro/2019
#
# Usage:
# make        # cria o executável monga_compiler
# make clean  # remove os temporários
.PHONY := all clean program

TMPPATH = tmp

SRCPATH = src

COMPILER = gcc
LINKER_FLAGS = -lfl
WARNING_FLAGS = -Wall #-fsanitize=address

INCLUDES = -I${SRCPATH}
#Faltam os defines
#DEFINES = -D${1}

PROG_NAME = Program
BIN_NAME = monga_compiler
COMPILER_OUTPUT = -o ${BIN_NAME}


SRC = ${SRCPATH}/tree_stitcher.c
GRAMMAR = ${SRCPATH}/monga_grammar.y
TMP_GRAMMAR_HEADER = ${SRCPATH}/definitions.h

LEXIC = ${SRCPATH}/monga_lexic.l
TMP_LEXIC_HEADER = ${SRCPATH}/lex_defs.h

TMP_GRAMMATIC = ${TMPPATH}/tmp_grammatic.c
TMP_LEXIC = ${TMPPATH}/tmp_lexic.c

C_FILES = ${SRC} ${TMP_GRAMMATIC} ${TMP_LEXIC} ${SRCPATH}/ast.c ${SRCPATH}/var_table.c ${SRCPATH}/code_generator.c

all: monga_compiler

monga_compiler: TMP_GRAMMATIC TMP_LEXIC
	@echo "Compilando ${BIN_NAME}..."
	@gcc ${WARNING_FLAGS} ${INCLUDES}  ${C_FILES} ${COMPILER_OUTPUT} ${LINKER_FLAGS}
	@echo

TMP_GRAMMATIC:
	@echo "Compilando gramática..."
	@yacc --output=${TMP_GRAMMATIC} --defines=${TMP_GRAMMAR_HEADER} ${GRAMMAR}
	@echo

TMP_LEXIC:
	@echo "Compilando léxico..."
	@flex --outfile=${TMP_LEXIC} --header-file=${TMP_LEXIC_HEADER} ${LEXIC} ${TMP_GRAMMAR_HEADER}
	@echo

program:
	@echo "Compilando Program.ll para executável Program..."
	@llc ${PROG_NAME}.ll
	@gcc ${WARNING_FLAGS} ${PROG_NAME}.s -o ${PROG_NAME}

clean:
	@echo "Limpando"
	-rm -f ${TMP_GRAMMATIC}
	-rm -f ${TMP_LEXIC}
	-rm -f ${BIN_NAME}
	-rm -f ${PROG_NAME}.ll
	-rm -f ${PROG_NAME}.s
	-rm -f ${PROG_NAME}
	@echo
