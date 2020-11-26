/**********************************************************************************************************************
Trabalho Computacional 1 – Programação II – 2015/2 – Engenharia de Computação
Aluno: André Luiz Piona de Araujo
**********************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int checarDecPalin (int num, int casas, int decimal[])   /*FUNÇÃO PARA CHECAR SE O NÚMERO DECIMAL É PALÍNDROMO*/
{
    int aux, aux2=0, palin=1;
    for (aux=casas;aux>0;aux--)     /*ELE TRANSFORMA O NÚMERO INTEIRO EM UM VETOR*/
    {
        decimal[casas-aux] = (num/pow(10,aux-1))-(aux2*10);
        aux2= (aux2*10)+decimal[casas-aux];
    }
    aux=0;
    for (aux=0;aux<casas;aux++)                 /*E COMPARA CADA DIGITO PARA CONFIRMAR SE É UM PALÍNDROMO*/
    {
        if (decimal[aux]!=decimal[casas-1-aux])
        {
            palin=0;
            aux=casas;
        }
    }
    return palin;  /*CASO SEJA PALÍNDROMO, RETORNA VALOR 'UM'. CASO CONTRÁRIO RETORNA 'ZERO'*/
}

int checarBinPalin (int num, int casas, int binario[]) /*FUNÇÃO PARA CHECAR SE O NÚMERO BINÁRIO É PALÍNDROMO*/
{
    int i, j, palin=1, valorBinario[20]={524288,262144,131072,65536,32768,16384,8192,4096,2048,1024,512,256,128,64,32,16,8,4,2,1}; /*VETOR COM O VALOR DE CADA CASA BÍNARIA*/
    for (i=0;i<20;i++)
    {
        if (num-valorBinario[i]>=0)                /*ELE COMPARA O NÚMERO DECIMAL COM OS VALORES BINÁRIOS, DO MAIOR PARA O MENOR*/
        {                                          /*QUANDO O VALOR É MAIOR OU IGUAL, ELE SUBTRAI ESSE VALOR E PASSA 'UM' PARA O VETOR BÍNARIO DO NÚMERO*/
            num=num-valorBinario[i];               /*CASO CONTRÁRIO PASSA 'ZERO', E REPETE O PROCESSO COM UM VALOR MENOR*/
            binario[i]=1;
        }
        else
        {
            binario[i]=0;
        }
    }
    i=0;
    while (binario[i]==0)          /*PARA O NÚMERO BÍNARIO NÃO COMEÇAR COM 'ZERO', ESSE "WHILE" PULA OS 'ZEROS' INICIAIS DO VETOR*/
    {
        i++;
    }
    for (j=19; j>=i;j--)           /*CONFERE SE O NÚMERO É PALÍNDROMO COMEÇANDO PELO PRIMEIRO 'UM' DO NÚMERO BÍNARIO*/
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
    for (i=0;i<2;i++)  /*É NECESSÁRIO CONFERIR DUAS VEZES QUANTOS NÚMEROS SÃO PALÍNDROMOS PARA PODER CRIAR UM VETOR COM NÚMERO DE CASAS IGUAL A QUANTIDADE DE NÚMEROS*/
    {
        if(i=1)
        {
            int vetor[palindromos];  /*NA SEGUNDA VEZ É CRIADO UM VETOR USANDO O CONTADOR DE NÚMEROS PALÍNDROMOS*/
        }
        for (num=0;num<=1000000;num++)      /*CONTADOR DE 'ZERO' À 'UM' MILHÃO*/
        {
            casas=1;
            aux=num;
            while (aux>9)           /*ESSE WHILE DIVIDE O NÚMERO POR 'DEZ' ATÉ SOBRAR APENAS O PRIMEIRO DÍGITO*/
            {
                aux=aux/10;
                casas++;
            }
            if (aux==num-((num/10)*10))           /*CONFERE O PRIMEIRO DÍGITO COM O ÚLTIMO DIGITO*/
            {                                     /*É FEITO A DIVISÃO POR 'DEZ' PARA RETIRAR O ÚLTIMO DIGITO*/

                palinDec = checarDecPalin (num,casas,decimal);          /*CHAMA A FUNÇÃO PARA VERIFICAR SE O NÚMERO DECIMAL É PALÍNDROMO*/
                if (palinDec==1)
                {
                    decimaisPalindromos++;                              /*SE FOR PALÍNDROMO, SOMA NO CONTADOR DE PALÍNDROMOS DECIMAIS E*/
                    palinBin = checarBinPalin (num,casas,binario);      /*CHAMA A FUNÇÃO PARA VERIFICAR SE É PALÍNDROMO EM BÍNARIO TAMBÉM*/
                }
                if ((palinDec==1)&&(palinBin==1))       /*CASO SEJA PALÍNDROMO EM DECIMAL E EM BÍNARIO, ADICIONA AO CONTATOR PARA BÍNARIOS E PARA AMBOS*/
                {
                    binariosPalindromos++;
                    palindromos++;
                    fprintf(escrever, "%d\n", num);     /*ESCREVE NO ARQUIVO DE TEXTO O NÚMERO PALÍNDROMO*/
                    if (i=2)
                    {
                        soma=soma+num;          /*O SOMATÓRIO DOS NÚMEROS ENCONTRADOS*/
                    }
                }
            }
        }
        float percentual = (binariosPalindromos/decimaisPalindromos)*100;  /*VÁRIAVEL COM O PERCENTUAL*/
        fprintf(escrever, "\nSomatoria dos números decimais acima é de %d\n", soma);
        fprintf(escrever, "\nO percentual de números palíndromos decimais, que também são palíndromos binários é de %.2f%%.", percentual );

    }
}
