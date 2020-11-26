#include <stdio.h>
#include <stdlib.h>
#include "wiked.h"

int main()
{
    TipoPagina* pagina = iniciaPag();           //cria a lista de paginas
    TipoEditor* editor = iniciaEdi();           //cria a lista de editores
    FILE *log, *entrada;
    if(!(log = fopen("log.txt", "w"))){         //abre o arquivo log.txt para relatorio
        printf("Erro ao escrever aqruivo log.txt\n");
    }
    char arqEntrada[50],comando[50], dado1[50], dado2[50], dado3[50], fim;
    printf("Insira o arquivo com a lista de comandos desejados.\n");
    scanf("%s", &arqEntrada);                   //recebe o nome do arquivo com os comando. O arquivo tem que estar no mesmo diretorio
    if (!(entrada = fopen(arqEntrada ,"r"))){   //abre o arquivo de entrada para leitura de comandos
        printf("Erro ao ler o arquivo de entrada\n");
        exit(0);
    }
    while(1){
        fscanf(entrada, "%s\n", comando);       //enquanto nao chegar no comando 'FIM' ira ficar no loop recebendo comandos e seus dados
        if (strcmp(comando,"INSEREPAGINA")==0){
            fscanf(entrada, "%s %s", dado1, dado2);
            pagina = INSEREPAGINA(log, pagina, dado1, dado2);
        }

        if (strcmp(comando,"RETIRAPAGINA")==0) {
            fscanf(entrada, "%s", dado1);
            pagina = RETIRAPAGINA(log, pagina, dado1);
        }

        if (strcmp(comando,"INSEREEDITOR")==0) {
            fscanf(entrada, "%s", dado1);
            editor = INSEREEDITOR(log, editor, dado1);                                      //um 'if' para cada comando possível que será comparado com o comando lido,
        }                                                                                   //até achar o 'if' com o comando lido.
                                                                                            //depois é lido os dados que também estará na lista de comandos, e é então
        if (strcmp(comando,"RETIRAEDITOR")==0) {                                            //executado o comando com os dados recebidos
            fscanf(entrada, "%s", dado1);
            editor = RETIRAEDITOR(log, editor, dado1);
        }

        if (strcmp(comando,"INSERECONTRIBUICAO")==0) {
            fscanf(entrada, "%s %s %s", dado1, dado2, dado3);
            pagina = INSERECONTRIBUICAO(log, pagina, editor, dado1, dado2, dado3);
        }

        if (strcmp(comando,"RETIRACONTRIBUICAO")==0) {
            fscanf(entrada, "%s %s %s", dado1, dado2, dado3);
            pagina = RETIRACONTRIBUICAO(log, pagina, dado1, dado2, dado3);
        }

        if (strcmp(comando,"INSERELINK")==0) {
            fscanf(entrada, "%s %s", dado1, dado2);
            pagina = INSERELINK(log, pagina, dado1, dado2);
        }

        if (strcmp(comando,"RETIRALINK")==0) {
            fscanf(entrada, "%s %s", dado1, dado2);
            pagina = INSERELINK(log, pagina, dado1, dado2);
        }

        if (strcmp(comando,"CAMINHO")==0) {
            fscanf(entrada, "%s %s", dado1, dado2);
            CAMINHO(log, pagina, dado1, dado2);
        }

        if (strcmp(comando,"IMPRIMEPAGINA")==0) {
            fscanf(entrada, "%s", dado1);
            IMPRIMEPAGINA(log, pagina, dado1);
        }

        if (strcmp(comando,"IMPRIMEWIKED")==0) {
            IMPRIMEWIKED(log, pagina);
        }

        if (strcmp(comando,"FIM")==0) {
            FIM(pagina,editor,log,entrada);
        }
    }
}
