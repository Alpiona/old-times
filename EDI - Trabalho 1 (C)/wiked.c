#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wiked.h"

struct link {
    struct link* proxLink;
    struct pagina* pag;             //struct links possui ponteiro para o proximo link da lista, ponteiro para a pagina q será o destino,
    char pagDest[50];               //e os nomes da pagina destino e do arquivo da pagina destino
    char arqPag[50];
};

struct editor {
    char nomeEdi[50];               //struct editor possui ponteiro para o proximo editor e nome do editor
    struct tipoeditor* proxEdi;
};

struct arquivo {
    struct arquivo* antArq;         //struct arquivo possui ponteiro para o proximo arquivo e para o anterior (para poder imprimir na ordem em que os arquivos vao sendo
    struct arquivo* proxArq;        //adicionados), nome do editor que irá adicionar o arquivo, e o nome do arquivo. Possui int 'ret' de retirado, que será usado como
    char nomeEdi[50];               //boolean para saber se o arquivo foi retirado ou não, pois o arquivo retirado devera ainda existir
    char nomeArq[50];
    int ret;
};

struct pagina {
    char nomePag[50];               //struct pagina possui ponteiro para a proxima pagina, e pagina anterior (pois como será o struct 'principal',
    char arqPag[50];                //facilita bastante), ponteiros para uma lista de links e arquivos ligados a pagina, além do nome da pagina e do arquivo da pagina
    struct link* link;
    struct arquivo* arq;
    struct tipopagina* proxPag;
    struct tipopagina* antPag;
};

TipoEditor* iniciaEdi(void){        //funcao de inicializacao para lista de editores
    return NULL;
}

TipoPagina* iniciaPag(void){        //funcao de inicializacao para lista de paginas
    return NULL;
}

TipoArquivo* INSEREARQUIVO (TipoArquivo* arq, char* editor, char* arquivo){
    TipoArquivo* novoArq = (TipoArquivo*) malloc (sizeof(TipoArquivo));
    strcpy (novoArq->nomeEdi, editor);
    strcpy (novoArq->nomeArq, arquivo);                                         //funcao para adicionar arquivo a lista de arquivos de determinada pagina, o 'ret'
    novoArq->proxArq=arq;                                                       //fica = a '0' pois só mudara para '1' quando a contribuicao do arquivo for retirado
    novoArq->antArq=NULL;
    novoArq->ret=0;
    if (arq!=NULL){
        arq->antArq= novoArq;
    }
    return novoArq;
}

TipoPagina* INSEREPAGINA (FILE *log, TipoPagina* pagina, char* nomePag, char* nomeArq){
    TipoPagina* verifica = pagina;
    while (verifica!=NULL){
        if (strcmp(verifica->nomePag, nomePag)==0){
            fprintf(log, "ERRO: Nao foi possivel criar pagina '%s' pois o nome da pagina ja foi utilizado.\n", nomePag);        //'while' com 2 'if' para verificar se
            return pagina;                                                                                                      //o nome da pagina ou o arquivo da pagina
        }                                                                                                                       // ja foi utilizado, caso tenha sido
        if (strcmp(verifica->arqPag, nomeArq)==0){                                                                              // sera escrito como erro no arquivo
            fprintf(log, "ERRO: Nao foi possivel criar pagina '%s' pois '%s' ja foi utilizado.\n", nomePag, nomeArq);           // log.txt, e finalizara a funcao
            return pagina;
        }
        verifica=verifica->proxPag;
    }
    TipoPagina* novaPag = (TipoPagina*) malloc (sizeof(TipoPagina));            //caso nao tenha sido encontrado nenhum erro,
    strcpy (novaPag->nomePag, nomePag);                                         //será adicionado a pagina a lista de paginas.
    strcpy (novaPag->arqPag, nomeArq);
    novaPag->arq=NULL;
    novaPag->link=NULL;                                                         //como a lista de links e arquivos só existem
    novaPag->proxPag=pagina;                                                    //dentro de struct 'pagina', nao foi necessario
    novaPag->antPag=NULL;                                                       //uma funcao separada para iniciar-los, são inicia-
    if (pagina!=NULL){                                                          //lizados sempre que uma pagina é criada
        pagina->antPag= novaPag;
    }
    return novaPag;
}

TipoPagina* RETIRAPAGINA (FILE *log, TipoPagina* pagina, char* nomePag){
    TipoPagina* novaPag = (TipoPagina*) malloc (sizeof(TipoPagina));
    TipoPagina* novaPag2 = (TipoPagina*) malloc (sizeof(TipoPagina));
    for (novaPag=pagina; strcmp(novaPag->nomePag,nomePag)!=0; novaPag=novaPag->proxPag){        //'for' para encontrar a pagina que devera ser retidada, com base no
            if (novaPag->proxPag==NULL){                                                        //nome dado, caso nao encontre, o erro sera escrito no log.txt seguido
                fprintf(log, "ERRO: Nao existe '%s' na lista de pagina.\n", nomePag);           //da finalizacao do programa
                return pagina;
            }
    }
    if (novaPag==pagina){
        pagina=novaPag->proxPag;                                                //caso enontrado sera feito a retirada da pagina da lista
    }
    else{
        novaPag2=novaPag->antPag;
        novaPag2->proxPag=novaPag->proxPag;                                     //OBs: foi necessario o "novaPag2" pois quando fazia "novaPag->antPag->proxPag" ou
    }                                                                           //"novaPag->proxPag->antPag" dava erro e a unica forma que encontrei de arrumar foi
    if (novaPag->proxPag!=NULL){                                                //essa, infelizmente tive que repetir esse metodo em outras funcoes
        novaPag2=novaPag->proxPag;
        novaPag2->antPag=novaPag->antPag;
    }
    free(novaPag);
    return pagina;
}

TipoEditor* INSEREEDITOR (FILE *log, TipoEditor* editor, char* nome){
    TipoEditor* valida = editor;
    while (valida!=NULL){
        if (strcmp(valida->nomeEdi,nome)==0){
            fprintf(log, "ERRO: Ja existe editor '%s' na lista de editores.\n", nome);          //caso o nome do editor já exista na lista, será escrito como erro no log
            return editor;                                                                      // e a funcao finalizada, caso contrario, será inserido normalmente
        }
        valida=valida->proxEdi;
    }
    TipoEditor* novoEdi = (TipoEditor*) malloc (sizeof (TipoEditor));
    strcpy (novoEdi->nomeEdi, nome);
    novoEdi->proxEdi=editor;
    return novoEdi;
}

TipoEditor* RETIRAEDITOR (FILE *log, TipoEditor* editor, char* nome){
    TipoEditor* novoEditor = editor;
    TipoEditor* anterior = NULL;
    while (strcmp(novoEditor->nomeEdi,nome)!=0){
        anterior=novoEditor;
        novoEditor= novoEditor->proxEdi;
        if (novoEditor==NULL){
            fprintf(log, "ERRO: Nao existe o editor '%s' para ser retirado.", nome);               //caso nao encontre o editor para ser retirado, sera escrito como erro
            return editor;                                                                         //no log.txt e a funcao finalizada, do contrario será retirado normalmente
        }
    }
    if (anterior == NULL){
        editor = novoEditor->proxEdi;
    }
    else{
        anterior->proxEdi=novoEditor->proxEdi;
    }
    free(novoEditor);
    return editor;
}

TipoPagina* INSERECONTRIBUICAO (FILE *log, TipoPagina* listaPag, TipoEditor* listaEdi, char* pagina, char* editor, char* arquivo){
    TipoEditor* lista1 = (TipoEditor*) malloc (sizeof(TipoEditor));
    for (lista1=listaEdi; strcmp(lista1->nomeEdi,editor)!=0;lista1=lista1->proxEdi){
        if (lista1->proxEdi==NULL){
            fprintf(log, "ERRO: Nao existe o editor '%s' para inserir uma contribuicao.\n", editor);        //é confirmado se existe o editor e a pagina, caso contrario
            return listaPag;                                                                                //é visto como erro
        }
    }

    TipoPagina* lista2 = (TipoPagina*) malloc (sizeof(TipoPagina));
    for (lista2=listaPag; strcmp(lista2->nomePag,pagina)!=0;lista2=lista2->proxPag){
        if (lista2->proxPag==NULL){
            fprintf(log, "ERRO: Nao existe pagina '%s' para inserir uma contribuicao.\n", pagina);
            return listaPag;
        }
    }
    lista2->arq = INSEREARQUIVO(lista2->arq, editor, arquivo);          //caso nao encontre nenhum erro, é usado a funcao 'INSEREARQUIVO' para adicionar a contribuicao
    while(lista2->antPag!=NULL){                                        //na lista de arquivos da pagina, apos isso é usado uma funcao 'while' para retornar a lista de
        lista2=lista2->antPag;                                          //paginas para o comeco antes de retornar a mesma
    }
    return lista2;
}

TipoPagina* RETIRACONTRIBUICAO (FILE *log, TipoPagina* listaPag, char* pagina, char* editor, char* arquivo){
    TipoPagina* novaPag = (TipoPagina*) malloc (sizeof(TipoPagina));
    for (novaPag=listaPag; strcmp(novaPag->nomePag,pagina)!=0;novaPag=novaPag->proxPag){
        if (novaPag->proxPag==NULL){
            fprintf("ERRO: Nao existe pagina '%s' para retirar a contribuicao.\n", pagina);  //confirma se a pagina existe
            return listaPag;
        }
    }
    if (novaPag->arq==NULL){
        fprintf(log, "ERRO: Nao possui nenhuma contribuição vinculado a essa pagina para ser retirado.\n");  //confirma se existe alguma contribuicao ligado a pagina
        return listaPag;
    }
    TipoArquivo* listaArq = (TipoArquivo*) malloc(sizeof(TipoArquivo));  //novamente tive que criar uma variavel pois dava erro, "novaPag->arq->proxArq" nao funcionava
    listaArq = novaPag->arq;
    while(strcmp(listaArq->nomeArq,arquivo)!=0){                    //confirma se o arquivo da contribuicao está na lista de arquivos da pagina
        if (listaArq->proxArq==NULL){
            fprintf(log, "ERRO: Nao existe o arquivo '%s' na pagina '%s' para retirar a contribuicao.\n",arquivo, pagina);
            return listaPag;
        }
        listaArq=listaArq->proxArq;
    }
    if (strcmp(listaArq->nomeEdi,editor)!=0){
        fprintf(log, "ERRO: Nao foi possivel retirar a contribuicao pois o arquivo '%s' nao foi editado por '%s'.\n", arquivo, editor);
        return listaPag;                                                    //confirma se o editor que irá retirar a contribuicao é o mesmo que adicionou
    }
    listaArq->ret=1;                            //caso nao tenha erros, o arquivo é marcado como "retirado" pela variavel 'ret'
    return listaPag;
}

TipoPagina* INSERELINK (FILE *log, TipoPagina* listaPag, char* pagOri, char* pagDest){
    TipoPagina* novaPag = (TipoPagina*) malloc(sizeof(TipoPagina));
    TipoLink* link = (TipoLink*) malloc(sizeof(TipoLink));
    novaPag=listaPag;
    if (novaPag==NULL){
        fprintf(log, "ERRO: Ainda nao existe nenhuma pagina para adicionar algum link.\n");     //confirma se existe alguma pagina criada
        return listaPag;
    }
    for (novaPag=listaPag; strcmp (novaPag->nomePag,pagDest)!=0;novaPag=novaPag->proxPag){
        if (novaPag->proxPag==NULL){
            fprintf(log, "ERRO: Nao existe pagina destino '%s' para criar link.\n", pagDest);       //confirma se pagina destino existe para o link desejado
            return listaPag;
        }
    }
    strcpy (link->pagDest, novaPag->nomePag);       //dados são inseridos ao struct link, para ser adicionado a lista de links da pagina
    strcpy (link->arqPag, novaPag->arqPag);
    link->pag=novaPag;
    for (novaPag=listaPag; strcmp(novaPag->nomePag,pagOri)!=0;novaPag=novaPag->proxPag){
        if (novaPag->proxPag==NULL){
            fprintf(log, "ERRO: Nao existe pagina origem '%s' para criar link.\n", pagOri);   //confirma de pagina origem existe para o link desejado
            return listaPag;
        }
    }
    link->proxLink=novaPag->link;
    novaPag->link=link;                                     //caso confirmado nenhum erro, o struct link com os dados é adicionado a lista
    while (novaPag->antPag!=NULL){
        novaPag=novaPag->antPag;                             //'novaPag' volta a ser o primeiro da lista para poder retornar
    }
    return novaPag;
}

TipoPagina* RETIRALINK(FILE *log, TipoPagina* listaPag, char* pagOri, char* pagDest){
    TipoPagina* novaPag = (TipoPagina*) malloc(sizeof(TipoPagina));
    for (novaPag=listaPag; strcmp (novaPag->nomePag,pagOri)!=0;novaPag=novaPag->proxPag){
        if (novaPag==NULL){
            fprintf(log, "ERRO: Ainda nao existe nenhuma pagina para poder retirar link.\n");  //confirma se existe alguma pagina
            return listaPag;
        }
        if (novaPag->proxPag==NULL){
            fprintf(log, "ERRO: Nao existe pagina origem '%s' para retirar link.\n", pagOri);  //confirma se existe a pagina de origem
            return listaPag;
        }
    }
    TipoLink* link = (TipoLink*) malloc(sizeof(TipoLink));
    TipoLink* anterior= NULL;
    link=novaPag->link;
    while (strcmp(link->pagDest, pagDest)!=0){
        anterior=link;                                                  //confirma se o link que devera ser retirado existe
        if(link->proxLink==NULL){
            fprintf(log, "ERRO: Nao existe link da pagina de origem '%s' para a pagina de destino '%s' para ser retirado. \n", pagOri, pagDest);
            return listaPag;
        }
        link=link->proxLink;
    }
    if (anterior==NULL){
        novaPag->link= link->proxLink;
        free(link);
        return listaPag;                                        //caso nao tenha nenhum erro, o link é retirado
    }
    else{
        anterior->proxLink=link->proxLink;
        free(link);
        return listaPag;
    }
}

void CAMINHO(FILE* log, TipoPagina* pagina, char* pagOri, char* pagDest){
    TipoPagina* origem = pagina;
    TipoPagina* destino = pagina;
    while (strcmp(origem->nomePag,pagOri)!=0){
        if (origem->proxPag==NULL){
            fprintf (log, "ERRO: Pagina origem '%s' nao existe para confirmar caminho.\n", pagOri);  //confirma se existe a pagina origem
            return;
           }
        origem=origem->proxPag;
    }
    while (strcmp(destino->nomePag, pagDest)!=0){
        if (destino->proxPag==NULL){
            fprintf (log, "ERRO: Pagina destino '%s' nao existe para confirmar caminho.\n", pagDest);  //confirma se existe a pagina destino
            return;
        }
        destino=destino->proxPag;
    }
    while (strcmp(origem->link->pagDest, pagDest)!=0){
        if (origem->link->proxLink == NULL){
            fprintf (log, "Nao ha caminho da pagina '%s' para pagina '%s'.\n", pagOri, pagDest);   //confirma se existe o caminho entre as 2 paginas, escrevendo no
            return;                                                                                //log.txt o resultado, independente de qual seja
        }
        origem->link= origem->link->proxLink;
    }
    fprintf (log, "Ha caminho da pagina '%s' paga pagina '%s'.\n", pagOri, pagDest);
    return;
}

void IMPRIMEPAGINA(FILE *log, TipoPagina* listaPag, char* pagina){
    TipoPagina* novaPag = (TipoPagina*) malloc(sizeof(TipoPagina));
    novaPag=listaPag;
    char ch;
    FILE *lerArquivo, *escreverPagina;
    while( strcmp(novaPag->nomePag,pagina)!=0){
            if (novaPag->proxPag==NULL){
                fprintf (log, "ERRO: Pagina inexistente para impressao.\n");        //confirma se a pagina requisitada existe
                return;
            }
            novaPag= novaPag->proxPag;
    }
    if (!(escreverPagina = fopen(novaPag->arqPag, "w"))){
        printf ("Erro ao escrever arquivo %s.txt\n", novaPag->nomePag);         //caso encontrda, o nome do arquivo da pagina é usado para criar variavel para
    }                                                                           //imprimir a pagina
    fprintf(escreverPagina, "%s",novaPag->nomePag);
    fprintf(escreverPagina, "\n\n--> Historico de Contribuicoes");
    if (novaPag->arq!=NULL){
        while (novaPag->arq->proxArq!=NULL){            //esse 'while' leva para o final da lista para poder ser impresso de tras para frente, assim sendo do
            novaPag->arq=novaPag->arq->proxArq;         //impresso em ordem na qual foi adicionado
        }
        while (novaPag->arq->antArq!=NULL){
            if (novaPag->arq->ret==0){
                fprintf(escreverPagina,"\n%s %s", novaPag->arq->nomeEdi, novaPag->arq->nomeArq);
            }
            else{
                fprintf(escreverPagina,"\n%s %s <<retirada>>", novaPag->arq->nomeEdi, novaPag->arq->nomeArq);       //tive que botar o 'while' e o 'if' pois caso bote
            }                                                                                                       //apenas um 'while' até "arq==NULL", nao conseguia
            novaPag->arq=novaPag->arq->antArq;                                                                      //voltar a lista para usa-la novamente na hora de
        }                                                                                                           //de pegar os textos de cada arquivo
        if (novaPag->arq->antArq==NULL){
            if (novaPag->arq->ret==0){
                fprintf(escreverPagina,"\n%s %s", novaPag->arq->nomeEdi, novaPag->arq->nomeArq);
            }
            else{
                fprintf(escreverPagina,"\n%s %s <<retirada>>", novaPag->arq->nomeEdi, novaPag->arq->nomeArq);
            }
        }
    }
    fprintf(escreverPagina, "\n\n--> Links");
    if(novaPag->link!=NULL){
        TipoLink* novoLink = novaPag->link;                                                         //escreve os links que a pagina possui
        while(novoLink!=NULL){
            fprintf(escreverPagina, "\n%s %s", novoLink->pagDest, novoLink->arqPag);
            novoLink=novoLink->proxLink;
        }
    }
    fprintf(escreverPagina, "\n\n--> Textos");
    if (novaPag->arq!=NULL){
        while (novaPag->arq->proxArq!=NULL){
            novaPag->arq=novaPag->arq->proxArq;         //novamente um 'while' para chegar no ultimo da lista, e inverter a ordem de impressao
        }
        while (novaPag->arq->antArq!=NULL){
            if (novaPag->arq->ret==0){
                fprintf(escreverPagina,"\n\n-------- %s (%s) --------\n\n", novaPag->arq->nomeArq, novaPag->arq->nomeEdi);
                if (!(lerArquivo = fopen(novaPag->arq->nomeArq, "r"))){
                    printf ("Erro ao ler arquivo %s.txt\n", novaPag->arq->nomeArq);
                }
                while (1) {
                    ch = fgetc(lerArquivo);
                    if (ch == EOF){
                        break;                          //um 'while' em loop para passar letra por letra de cada arquivo da lista de contribuicao,
                    }                                   //até chegar ao final do arquivo
                    else{
                        putc(ch, escreverPagina);
                    }
                }
                fclose(lerArquivo);
            }
            novaPag->arq=novaPag->arq->antArq;
        }
        if (novaPag->arq->antArq==NULL){
            if (novaPag->arq->ret==0){
                fprintf(escreverPagina,"\n\n-------- %s (%s) --------\n\n", novaPag->arq->nomeArq, novaPag->arq->nomeEdi);
                if (!(lerArquivo = fopen(novaPag->arq->nomeArq, "r"))){
                    printf ("Erro ao ler arquivo %s.txt\n", novaPag->arq->nomeArq);
                }
                while (1) {
                    ch = fgetc(lerArquivo);                                 //novamente fiz um 'while' e 'if' ao inves de apenas um 'while' para nao botar o "arq==NULL",
                    if (ch == EOF){                                         //porem depois vi que nao era necessario, mas por algum motivo, o arquivo "fisica.txt"
                        break;                                              //do exemplo, saia sem conteudo. =/
                    }
                    else{
                        putc(ch, escreverPagina);
                    }
                }
                fclose(lerArquivo);
            }
        }
    }
    fclose(escreverPagina);
    return;
}

void IMPRIMEWIKED(FILE *log, TipoPagina* pagina){
    TipoPagina* novaPag = (TipoPagina*) malloc (sizeof (TipoPagina));
    for(novaPag=pagina;novaPag!=NULL;novaPag=novaPag->proxPag){                 //essa funcao apenas usa a funcao "IMPRIMEPAGINA" para cada pagina na lista, ate
        IMPRIMEPAGINA(log, novaPag, novaPag->nomePag);                          //imprimir todas
        if (novaPag->proxPag==NULL){
            return;
        }
    }
    return;
}

void FIM (TipoPagina* pagina, TipoEditor* editor, FILE* log, FILE* entrada){
    free(pagina);
    free(editor);
    free(log);                      ////no comando 'FIM' todas as memórias são liberadas e o programa finalizado
    free(entrada);
    exit(0);
}

