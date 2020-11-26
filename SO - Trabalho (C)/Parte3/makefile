#Para escrever comentários ##
############################# Makefile ##########################
all: Parte3
Parte3: spsh.o 
        # O compilador faz a ligação entre os dois objetos
		gcc -o Parte3 spsh.o -lpthread
#-----> Distancia  com o botão TAB ### e não com espaços
Parte3.o: spsh.c
		gcc -o spsh.o -c spsh.c -W -Wall -pedantic
clean:
		rm -rf *.o Parte3
run: Parte3
	./Parte3
