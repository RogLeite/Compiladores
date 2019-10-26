
.PHONY := all say_hello generate clean
COMANDO := touch

all: say_hello generate

say_hello:
	@echo "Oi"

generate:
	@echo "Criando arquivos de texto..."
	${COMANDO} tmp/file-{1..10}.txt

clean:
	@echo "Limpando..."
	rm tmp/file-*.txt
