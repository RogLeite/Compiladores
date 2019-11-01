.PHONY := all clean
FILENAME = basic

all: ${FILENAME}


${FILENAME}: ${FILENAME}.s
	@echo "Compiling .s..."
	@gcc -fsanitize=address ${FILENAME}.s -o ${FILENAME}

${FILENAME}.s: ${FILENAME}.ll
	@echo "Compiling .ll..."
	@llc ${FILENAME}.ll

${FILENAME}.ll:
	@echo "Emiting llvm..."
	@clang ${FILENAME}.c -S -emit-llvm


clean:
	@echo "Removing ${FILENAME}..."
	@rm ${FILENAME}
	@echo "Removing ${FILENAME}.s..."
	@rm ${FILENAME}.s
	@echo "Removing ${FILENAME}.l..."
	@rm ${FILENAME}.ll
