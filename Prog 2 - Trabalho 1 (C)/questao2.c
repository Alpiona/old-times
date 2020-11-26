/**********************************************************************************************************************
Trabalho Computacional 1 – Programação II – 2015/2 – Engenharia de Computação
Aluno: André Luiz Piona de Araujo
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
    if (!(escrever = fopen ("saida.txt", "w"))) /*SELECIONANDO QUAL SERÁ ARQUIVO DE SAIDA.*/
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
            i=i-2;  /*PARA NÃO PRECISAR REINICIAR O CONTADOR, VOLTA APENAS AO NOME ANTERIOR AO COMPARADO*/
        }           /* POR EXEMPLO, UM NUMERO QUE ESTÁ EM 5º MAS TEM QUE IR PARA O 3º, SERÁ FEITO A COMPARAÇÃO DO 5º COM 4º, DEPOIS DO 4º COM 3º*/
    }               /*  E DO 3º COM 2º, COMO NÃO SERÁ FEITO A TROCA NO ÚLTIMO CASO, O CONTADOR CONTINUA NOVAMENTE, SEM A NECESSIDADE DE COMPARAR COM O 1º.*/
    for (i=0;i<5163;i++)
    {
        for (j=0;j<30;j++)
        {
            if (nomesAlfa[i][j]!=0)
            {
                nomesPont[i][j]=nomesAlfa[i][j]-64; /*TRANSFORMAÇÃO DE CADA LETRA PARA SEUS VALORES, EXCLUINDO OS ESPAÇOS VAZIOS NAS STRINGS.*/
            }
            nomesAux[i][j]=nomesAlfa[i][j]; /*CRIANDO UMA SEGUNDA MATRIX COM OS NOMES, PARA NO FINAL TER UMA MATRIX COM ORDEM ALFABETICA E OUTRA COM ORDEM DE PONTUAÇÃO*/
        }                                   /*E COMO SERÁ NECESSÁRIO A POSIÇÃO ALFABETICA PARA A PONTUAÇÃO, COPIEI A MATRIX JÁ NA ORDEM.*/
    }
     for (i=0;i<5163;i++)
    {
        for (j=0;j<30;j++)
        {
            nomesPontSoma[i]=nomesPontSoma[i]+nomesPont[i][j]; /*SOMA DAS LETRAS DE CADA PALAVRA.*/
        }
        nomesPontSoma[i]=nomesPontSoma[i]*(i+1); /*A SOMATÓRIA É MULTIPLICADA PELA POSIÇÃO DO NOME.*/
    }
    for (i=5162;i>0;i--)
    {
        if (nomesPontSoma[i]>nomesPontSoma[i-1])
        {
            strcpy (auxChar, nomesAux[i]);                  /*TROCA DE POSIÇÃO DE ACORDO COM A PONTUAÇÃO.*/
            strcpy (nomesAux[i], nomesAux[i-1]);
            strcpy (nomesAux[i-1], auxChar);                /*A TROCA OCORRE TANTO NO VETOR COM A PONTUAÇÃO, QUANTO*/
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
            fprintf(escrever,"O nome %s está na posição %d nas 2 listas.", nomesAux[i], i);      /*PROCURANDO NOMES NA MESMA POSIÇÃO EM AMBAS AS LISTAS*/
            j++;
        }
    }
    if (j==0)
    {
         fprintf(escrever,"Não possui nomes ocupando uma mesma posição em ambas as listas.\n\n"); /*CASO NÃO ENCONTRE, SERÁ DADO O AVISO*/
    }
    fprintf(escrever,"POSIÇÃO//ORDEM ALFABETICA//ORDEM POR PONTUAÇÃO\n\n"); /*PARA MELHOR ORGANIZAÇÃO*/
    for (i=0;i<5163;i++)
    {
        fprintf(escrever, "%dº//%s//%s(%d)\n", (i+1), nomesAlfa[i],nomesAux[i],nomesPontSoma[i]); /*O ARQUIVO FINAL*/
    }
}
