#Para escrever comentários ##
############################# Makefile ##########################
all: Parte2
Parte2: parte2.o 
        # O compilador faz a ligação entre os dois objetos
		gcc -o Parte2 parte2.o -lpthread
#-----> Distancia  com o botão TAB ### e não com espaços
Parte2.o: parte2.c
		gcc -o parte2.o -c parte2.c -W -Wall -pedantic
clean:
		rm -rf *.o Parte2
run: Parte2
	./Parte2
