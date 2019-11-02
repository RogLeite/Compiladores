.PHONY := all clean
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


clean:
	@echo "Removing ${SRC}..."
	@rm ${SRC}
	@echo "Removing ${SRC}.s..."
	@rm ${SRC}.s
	@echo "Removing ${SRC}.ll..."
	@rm ${SRC}.ll
