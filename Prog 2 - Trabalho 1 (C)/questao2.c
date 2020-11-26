/**********************************************************************************************************************
Trabalho Computacional 1 � Programa��o II � 2015/2 � Engenharia de Computa��o
Aluno: Andr� Luiz Piona de Araujo
**********************************************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main ()
{

    int i, j, nomesPont[5163][30]={0}, nomesPontSoma[5163]={0}, auxInt;
    char nomesAlfa[5163][30], nomesAux[5163][30], auxChar[30];
    FILE *ler;
    if (!(ler = fopen ("nomes.txt", "r"))) /*LEITURA DO ARQUIVO DE TEXTO COM OS NOMES.*/
    {
        printf ("\nErro");
    }
    FILE *escrever;
    if (!(escrever = fopen ("saida.txt", "w"))) /*SELECIONANDO QUAL SER� ARQUIVO DE SAIDA.*/
    {
        printf ("\nErro");
    }
    for (i=0;i<5163;i++)
    {
        fscanf(ler, "%s ", &nomesAlfa[i]); /*RECEBER TODOS OS NOMES NO ARQUIVO DE ORIGEM.*/
    }
    for (i=0;i<5162;i++)
    {
        if (strcmp (nomesAlfa[i],nomesAlfa[i+1])==1)  /*BOTAR EM ORDEM ALFABETICAMENTE OS NOMES RECEBIDOS.*/
        {
            strcpy (auxChar, nomesAlfa[i]);
            strcpy (nomesAlfa[i], nomesAlfa[i+1]);
            strcpy (nomesAlfa[i+1], auxChar);
            i=i-2;  /*PARA N�O PRECISAR REINICIAR O CONTADOR, VOLTA APENAS AO NOME ANTERIOR AO COMPARADO*/
        }           /* POR EXEMPLO, UM NUMERO QUE EST� EM 5� MAS TEM QUE IR PARA O 3�, SER� FEITO A COMPARA��O DO 5� COM 4�, DEPOIS DO 4� COM 3�*/
    }               /*  E DO 3� COM 2�, COMO N�O SER� FEITO A TROCA NO �LTIMO CASO, O CONTADOR CONTINUA NOVAMENTE, SEM A NECESSIDADE DE COMPARAR COM O 1�.*/
    for (i=0;i<5163;i++)
    {
        for (j=0;j<30;j++)
        {
            if (nomesAlfa[i][j]!=0)
            {
                nomesPont[i][j]=nomesAlfa[i][j]-64; /*TRANSFORMA��O DE CADA LETRA PARA SEUS VALORES, EXCLUINDO OS ESPA�OS VAZIOS NAS STRINGS.*/
            }
            nomesAux[i][j]=nomesAlfa[i][j]; /*CRIANDO UMA SEGUNDA MATRIX COM OS NOMES, PARA NO FINAL TER UMA MATRIX COM ORDEM ALFABETICA E OUTRA COM ORDEM DE PONTUA��O*/
        }                                   /*E COMO SER� NECESS�RIO A POSI��O ALFABETICA PARA A PONTUA��O, COPIEI A MATRIX J� NA ORDEM.*/
    }
     for (i=0;i<5163;i++)
    {
        for (j=0;j<30;j++)
        {
            nomesPontSoma[i]=nomesPontSoma[i]+nomesPont[i][j]; /*SOMA DAS LETRAS DE CADA PALAVRA.*/
        }
        nomesPontSoma[i]=nomesPontSoma[i]*(i+1); /*A SOMAT�RIA � MULTIPLICADA PELA POSI��O DO NOME.*/
    }
    for (i=5162;i>0;i--)
    {
        if (nomesPontSoma[i]>nomesPontSoma[i-1])
        {
            strcpy (auxChar, nomesAux[i]);                  /*TROCA DE POSI��O DE ACORDO COM A PONTUA��O.*/
            strcpy (nomesAux[i], nomesAux[i-1]);
            strcpy (nomesAux[i-1], auxChar);                /*A TROCA OCORRE TANTO NO VETOR COM A PONTUA��O, QUANTO*/
            auxInt=nomesPontSoma[i];                        /*NA MATRIX CRIADA PARA ORGANIZAR OS NOMES NA MESMA ORDEM.*/
            nomesPontSoma[i]=nomesPontSoma[i-1];
            nomesPontSoma[i-1]=auxInt;
            i=i+2;
        }
    }
    j=0;
    for (i=0;i<5163;i++)
    {
        if (strcmp (nomesAlfa[i],nomesAux[i])==0)
        {
            fprintf(escrever,"O nome %s est� na posi��o %d nas 2 listas.", nomesAux[i], i);      /*PROCURANDO NOMES NA MESMA POSI��O EM AMBAS AS LISTAS*/
            j++;
        }
    }
    if (j==0)
    {
         fprintf(escrever,"N�o possui nomes ocupando uma mesma posi��o em ambas as listas.\n\n"); /*CASO N�O ENCONTRE, SER� DADO O AVISO*/
    }
    fprintf(escrever,"POSI��O//ORDEM ALFABETICA//ORDEM POR PONTUA��O\n\n"); /*PARA MELHOR ORGANIZA��O*/
    for (i=0;i<5163;i++)
    {
        fprintf(escrever, "%d�//%s//%s(%d)\n", (i+1), nomesAlfa[i],nomesAux[i],nomesPontSoma[i]); /*O ARQUIVO FINAL*/
    }
}
