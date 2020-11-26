/**********************************************************************************************************************
Trabalho Computacional 1 � Programa��o II � 2015/2 � Engenharia de Computa��o
Aluno: Andr� Luiz Piona de Araujo
**********************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int checarDecPalin (int num, int casas, int decimal[])   /*FUN��O PARA CHECAR SE O N�MERO DECIMAL � PAL�NDROMO*/
{
    int aux, aux2=0, palin=1;
    for (aux=casas;aux>0;aux--)     /*ELE TRANSFORMA O N�MERO INTEIRO EM UM VETOR*/
    {
        decimal[casas-aux] = (num/pow(10,aux-1))-(aux2*10);
        aux2= (aux2*10)+decimal[casas-aux];
    }
    aux=0;
    for (aux=0;aux<casas;aux++)                 /*E COMPARA CADA DIGITO PARA CONFIRMAR SE � UM PAL�NDROMO*/
    {
        if (decimal[aux]!=decimal[casas-1-aux])
        {
            palin=0;
            aux=casas;
        }
    }
    return palin;  /*CASO SEJA PAL�NDROMO, RETORNA VALOR 'UM'. CASO CONTR�RIO RETORNA 'ZERO'*/
}

int checarBinPalin (int num, int casas, int binario[]) /*FUN��O PARA CHECAR SE O N�MERO BIN�RIO � PAL�NDROMO*/
{
    int i, j, palin=1, valorBinario[20]={524288,262144,131072,65536,32768,16384,8192,4096,2048,1024,512,256,128,64,32,16,8,4,2,1}; /*VETOR COM O VALOR DE CADA CASA B�NARIA*/
    for (i=0;i<20;i++)
    {
        if (num-valorBinario[i]>=0)                /*ELE COMPARA O N�MERO DECIMAL COM OS VALORES BIN�RIOS, DO MAIOR PARA O MENOR*/
        {                                          /*QUANDO O VALOR � MAIOR OU IGUAL, ELE SUBTRAI ESSE VALOR E PASSA 'UM' PARA O VETOR B�NARIO DO N�MERO*/
            num=num-valorBinario[i];               /*CASO CONTR�RIO PASSA 'ZERO', E REPETE O PROCESSO COM UM VALOR MENOR*/
            binario[i]=1;
        }
        else
        {
            binario[i]=0;
        }
    }
    i=0;
    while (binario[i]==0)          /*PARA O N�MERO B�NARIO N�O COME�AR COM 'ZERO', ESSE "WHILE" PULA OS 'ZEROS' INICIAIS DO VETOR*/
    {
        i++;
    }
    for (j=19; j>=i;j--)           /*CONFERE SE O N�MERO � PAL�NDROMO COME�ANDO PELO PRIMEIRO 'UM' DO N�MERO B�NARIO*/
    {
        if (binario[i]!=binario[j])
        {
            palin=0;
            i=20;
            j=i;
        }
        i++;
    }
    return palin;
}


int main ()
{
    int i, soma=0, palindromos=0, casas, palinBin=1, palinDec=1, binario[20], num, decimal[7], aux=0;
    float decimaisPalindromos=0, binariosPalindromos=0;
    FILE *escrever;
    if (!(escrever = fopen ("saida.txt", "w")))
    {
        printf ("\nErro");
    }
    for (i=0;i<2;i++)  /*� NECESS�RIO CONFERIR DUAS VEZES QUANTOS N�MEROS S�O PAL�NDROMOS PARA PODER CRIAR UM VETOR COM N�MERO DE CASAS IGUAL A QUANTIDADE DE N�MEROS*/
    {
        if(i=1)
        {
            int vetor[palindromos];  /*NA SEGUNDA VEZ � CRIADO UM VETOR USANDO O CONTADOR DE N�MEROS PAL�NDROMOS*/
        }
        for (num=0;num<=1000000;num++)      /*CONTADOR DE 'ZERO' � 'UM' MILH�O*/
        {
            casas=1;
            aux=num;
            while (aux>9)           /*ESSE WHILE DIVIDE O N�MERO POR 'DEZ' AT� SOBRAR APENAS O PRIMEIRO D�GITO*/
            {
                aux=aux/10;
                casas++;
            }
            if (aux==num-((num/10)*10))           /*CONFERE O PRIMEIRO D�GITO COM O �LTIMO DIGITO*/
            {                                     /*� FEITO A DIVIS�O POR 'DEZ' PARA RETIRAR O �LTIMO DIGITO*/

                palinDec = checarDecPalin (num,casas,decimal);          /*CHAMA A FUN��O PARA VERIFICAR SE O N�MERO DECIMAL � PAL�NDROMO*/
                if (palinDec==1)
                {
                    decimaisPalindromos++;                              /*SE FOR PAL�NDROMO, SOMA NO CONTADOR DE PAL�NDROMOS DECIMAIS E*/
                    palinBin = checarBinPalin (num,casas,binario);      /*CHAMA A FUN��O PARA VERIFICAR SE � PAL�NDROMO EM B�NARIO TAMB�M*/
                }
                if ((palinDec==1)&&(palinBin==1))       /*CASO SEJA PAL�NDROMO EM DECIMAL E EM B�NARIO, ADICIONA AO CONTATOR PARA B�NARIOS E PARA AMBOS*/
                {
                    binariosPalindromos++;
                    palindromos++;
                    fprintf(escrever, "%d\n", num);     /*ESCREVE NO ARQUIVO DE TEXTO O N�MERO PAL�NDROMO*/
                    if (i=2)
                    {
                        soma=soma+num;          /*O SOMAT�RIO DOS N�MEROS ENCONTRADOS*/
                    }
                }
            }
        }
        float percentual = (binariosPalindromos/decimaisPalindromos)*100;  /*V�RIAVEL COM O PERCENTUAL*/
        fprintf(escrever, "\nSomatoria dos n�meros decimais acima � de %d\n", soma);
        fprintf(escrever, "\nO percentual de n�meros pal�ndromos decimais, que tamb�m s�o pal�ndromos bin�rios � de %.2f%%.", percentual );

    }
}
