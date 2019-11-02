.PHONY := all clean remake
SRC = basic

all: ${SRC}


${SRC}: ${SRC}.s
	@echo "Compiling .s..."
	@clang ${SRC}.s -o ${SRC}

${SRC}.s: ${SRC}.ll
	@echo "Compiling .ll..."
	@llc ${SRC}.ll

${SRC}.ll:
	@echo "Emiting llvm..."
	@clang -O0 ${SRC}.c -S -emit-llvm

remake:
	-@rm -f ${SRC}.s
	-@rm -f ${SRC}
	@echo "Compiling from ${SRC}.ll"
	@llc ${SRC}.ll
	@clang ${SRC}.s -o ${SRC}

clean:
	@echo "Removing ${SRC}..."
	-@rm -f ${SRC}
	@echo "Removing ${SRC}.s..."
	-@rm -f ${SRC}.s
	@echo "Removing ${SRC}.ll..."
	-@rm -f ${SRC}.ll
