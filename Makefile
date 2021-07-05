#Compilar e Executar
all: compile
	./executavel
	reset

#Compila e cria o executavel
compile: main.o editor.o
	gcc main.o editor.o -o executavel

#dependencias
main.o: main.c
	gcc -c main.c

editor.o: editor.c
	gcc -c editor.c

#Remover os arquivos .o e Limpar a tela totalmente
reset:
	rm -rf executavel *.o *.gch
	reset