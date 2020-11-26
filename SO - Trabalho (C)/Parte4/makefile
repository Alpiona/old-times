#Para escrever comentários ##
############################# Makefile ##########################
all: Parte4
Parte4: parte4.o 
        # O compilador faz a ligação entre os dois objetos
		gcc -o Parte4 parte4.o -lpthread
#-----> Distancia  com o botão TAB ### e não com espaços
Parte4.o: parte4.c
		gcc -o parte4.o -c parte4.c -W -Wall -pedantic
clean:
		rm -rf *.o Parte4 Parte4-FIFO
run: Parte4
	./Parte4
