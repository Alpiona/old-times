#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void dadosRobos (int robosX[50][30], int robosY[50][30], int robosId[50]){
    FILE *lerRobos;
    if  (!(lerRobos = fopen("robos.txt", "r"))){
        printf ("erro robos.txt");
    }

    char auxString[50], auxString2[50];
    int auxInt , j=0, i=0, n=0, qntCoord[50], teste, id=0;
    for (i=0;i<50;i++){
        robosId[i]=0;
        qntCoord[i]=0;
        for (n=0;n<30;n++){
            robosX[i][n]=0;
            robosY[i][n]=0;
        }
    }
    n=0;
    i=0;
    fscanf(lerRobos, "%s", auxString);
    fscanf(lerRobos, "%s", auxString);
    while (i!=1){
        while (auxString[1]!=':'&&auxString[2]!=':'){
            fscanf(lerRobos, "%s", auxString);
            n++;
            if (strcmp(auxString, auxString2)==0){
                i=1;
                auxString[1]=':';
            }
            strcpy (auxString2, auxString);
        }
        qntCoord[j]=n;
        fscanf(lerRobos, "%s", auxString);
        n=0;
        j++;
    }
    rewind(lerRobos);
    for (i=0;i<50;i++){
        n=qntCoord[i];
        fscanf(lerRobos, "%d:", &robosId[i]);
        auxInt = n;
        while (n>0){
            fscanf(lerRobos, "%d,%d;", &robosX[i][auxInt-n], &robosY[i][auxInt-n]);
            n--;
        }
        if (qntCoord[i]==0){
            i=49;
        }
    }
    fclose(lerRobos);
}

void dadosCAs (int CAsX[50], int CAsY[50], int CAsCapac[50]){
    FILE *lerCAs;
    if  (!(lerCAs = fopen("CAs.txt", "r"))){
        printf ("erro CAs.txt");
    }
    int i;
    for (i=0;i<50;i++){
        fscanf(lerCAs, "%d,%d:%d;", &CAsX[i], &CAsY[i], &CAsCapac[i]);
        if (CAsX[i]==CAsX[i-1]&&CAsY[i]==CAsY[i-1]){
            i=50;
            CAsX[i]=0;
            CAsY[i]=0;
        }
    }
    fclose (lerCAs);
}

void dadosSobreviventes (int sobrevX[50], int sobrevY[50], int sobrevQnt[50]){

    FILE *lerSobreviventes;
    if  (!(lerSobreviventes = fopen("sobreviventes.txt", "r"))){
        printf ("erro sobreviventes.txt");
    }
    int i;
    for (i=0;i<50;i++){
        sobrevQnt[i]=0;
        sobrevY[i]=0;
        sobrevX[i]=0;
    }
    for (i=0;i<50;i++){
        fscanf(lerSobreviventes, "%d,%d:%d;", &sobrevX[i], &sobrevY[i], &sobrevQnt[i]);
        if (sobrevX[i]==sobrevX[i-1]&&sobrevY[i]==sobrevY[i-1]){
            sobrevX[i]=0;
            sobrevY[i]=0;
            i=50;
        }
    }
    fclose (lerSobreviventes);
}

void calcularDistanciaTotal (int robosX[50][30], int robosY[50][30], float distanciaTotal[50]){
    int i,j;
    for (i=0;i<50;i++){
        distanciaTotal[i]=0;
        for(j=0;j<30;j++){
            if (robosX[i][j+1]!=0&&robosY[j+1]!=0){
                distanciaTotal[i]=distanciaTotal[i]+(sqrt(pow((robosX[i][j+1] - robosX[i][j]),2) + pow((robosY[i][j+1]-robosY[i][j]),2)));
                }
            else{
                j=29;
            }
        }
        if (distanciaTotal[i]==0){
            i=49;
        }
    }
}

void calcularTempoTotal(float distanciaTotal[50], float tempoTotal[50]){
    int i;
    for (i=0;i<50;i++){
        tempoTotal[i]= distanciaTotal[i]/12;
        if (distanciaTotal[i]==0){
            i=49;
        }
    }
}

void encontrarRoboProximo (int robosX[50][30],int robosY[50][30], int sobrevX[50], int sobrevY[50], int robosSobrev[50][30]){
    int i, j, k, aux, auxCord, sobrevRobo[50], salvamento=0;
    float distancia, menorDist=5;
    for (i=0;i<50;i++){
        sobrevRobo[i]=0;
        for (j=0;j<30;j++){
            robosSobrev[i][j]=-1;
        }
    }
    for (k=0;k<50;k++){
        for (i=0;i<50;i++){
            if (robosX[i][1]!=0&&robosY[i][1]!=0){
                for (j=0;j<30;j++){
                    distancia = (sqrt(pow((robosX[i][j] - sobrevX[k]),2) + pow((robosY[i][j]-sobrevY[k]),2)));

                    if (distancia<=menorDist){
                        menorDist=distancia;
                        sobrevRobo[k]=i;
                        auxCord=j;
                        salvamento=1;
                    }
                    if (robosX[i][j+1]==0&&robosY[i][j+1]==0){
                        j=49;
                    }
                }
            }
            else{
                i=49;
            }
        }
        if (salvamento==1){
            robosSobrev[(sobrevRobo[k])][auxCord]=k;
            salvamento=0;
        }
        if (sobrevX[k+1]==0&&sobrevY[k+1]==0){
            k=49;
        }
        menorDist=5;
    }
    for (i=0;i<50;i++){
        for (j=0;j<30;j++){
            if(robosSobrev[i][j]>=0){
                for(k=29;k>j;k--){
                    robosX[i][k+1]=robosX[i][k];
                    robosY[i][k+1]=robosY[i][k];
                    robosSobrev[i][k]=robosSobrev[i][k-1];
                }
                robosX[i][j+1]=sobrevX[(robosSobrev[i][j])];
                robosY[i][j+1]=sobrevY[(robosSobrev[i][j])];
                robosSobrev[i][j]=-1;
                j++;
            }
        }
    }
}

void arquivoTrajetos (int robosId[50], int robosX[50][30], int robosY[50][30], int robosSobrev[50][30], int sobrevQnt[50], float distanciaTotal[50], float tempoTotal[50]){
    int i, j;
    FILE *escreverTrajeto;
    if  (!(escreverTrajeto = fopen("trajeto.txt", "w"))){
        printf ("erro trajeto.txt");
    }
    for (i=0;i<50;i++){
        fprintf (escreverTrajeto, "%d: ", robosId[i]);
        for (j=0;j<30;j++){
            fprintf (escreverTrajeto, "(%d,%d)%d;  ", robosX[i][j], robosY[i][j], sobrevQnt[(robosSobrev[i][j])]);
            if (robosX[i][j+1]==0&&robosY[i][j+1]==0){
                j=29;
            }
        }
        fprintf(escreverTrajeto, "Distancia Total: %f; Tempo Total: %f\n", distanciaTotal[i], tempoTotal[i]);
        if (robosId[i+1]==0){
            i=49;
        }
    }
    fclose(escreverTrajeto);
}

void arquivoHerois (int robosId[50], int robosSobrev[50][30], int sobrevQnt[50], float distanciaTotal[50], int sobrevTotal[50]){
    FILE *escreverHerois;
    if  (!(escreverHerois = fopen("herois.txt", "w"))){
        printf ("erro herois.txt");
    }
    int i, j, maiorQnt=0, igual=0;
    float eficiencia[50],maiorEficiencia=0;

    for (i=0;i<50;i++){
        sobrevTotal[i]=0;
        for (j=0;j<30;j++){
            if (robosSobrev[i][j]>=0){
             sobrevTotal[i]= sobrevTotal[i]+ sobrevQnt[(robosSobrev[i][j])];
            }
        }
        eficiencia[i]=sobrevTotal[i]/distanciaTotal[i];

        if (maiorQnt<=sobrevTotal[i]){
            maiorQnt=sobrevTotal[i];
        }
        if (maiorEficiencia<=eficiencia[i]){
            maiorEficiencia=eficiencia[i];
        }
        if (distanciaTotal[i+1]==0){
            i=49;
        }
    }
    fprintf(escreverHerois, "O(s) robô(s) que mais salvou(aram) foi(ram): ");
    for (i=0;i<50;i++){
        if (sobrevTotal[i]==maiorQnt){
            fprintf(escreverHerois, "%d# ", robosId[i]);
        }
        if (maiorEficiencia==eficiencia[i]&&maiorQnt==sobrevTotal[i]){
            igual=1;
        }
    }
    fprintf(escreverHerois, "\n\n");
    for (i=0;i<50;i++){
        fprintf(escreverHerois, "Robô %d# possui uma eficiência de %f com %d pessoas salvas.\n", robosId[i], eficiencia[i], sobrevTotal[i]);
        if (robosId[i+1]==0){
            i=49;
        }
    }
    fprintf(escreverHerois, "\n");
    if (igual==1){
        fprintf(escreverHerois, "O robô mais eficiente também é o que salvou mais pessoas.");
    }
    else{
        fprintf(escreverHerois, "O robô mais eficiente não é o que salvou mais pessoas.");
    }
    fclose(escreverHerois);
}

void arquivoAtendidos (int robosX[50][30], int robosY[50][30], int CAsX[50], int CAsY[50], int CAsCapac[50], int sobrevTotal[50]){
    FILE *escreverAtendidos;
    if  (!(escreverAtendidos = fopen("atendidos.txt", "w"))){
        printf ("erro atendidos.txt");
    }
    int i,j=0,x[50],y[50], aux, CAsPresentes[50], sobra=0, total=0;
    float distancia=0, menor=142;
    for (i=0;i<50;i++){
        CAsPresentes[i]=0;
    }
    for (i=0;i<50;i++){
        while (robosX[i][j+1]!=0&&robosY[i][j+1]!=0){
            j++;
        }
        x[i]=robosX[i][j];
        y[i]=robosY[i][j];
        if (robosX[i+1][1]==0&&robosY[i+1][1]==0){
            i=49;
        }
    }
    for (i=0;i<50;i++){
        while (sobrevTotal[i]>0){

            for (j=0;j<50;j++){
                distancia= (sqrt(pow((x[i] - CAsX[j]),2) + pow((y[i]-CAsY[j]),2)));
                if (distancia<=menor&&CAsPresentes[j]!=CAsCapac[j]){
                    menor=distancia;
                    aux=j;
                }
                if (CAsX[j+1]==0&&CAsY[j+1]==0){
                    j=49;
                }
            }
            if (menor<142){
                CAsPresentes[aux]=CAsPresentes[aux]+sobrevTotal[i];
                CAsPresentes[aux]=CAsPresentes[aux]-CAsCapac[aux];
                if (CAsPresentes[aux]>0){
                    sobrevTotal[i]=CAsPresentes[aux];
                    CAsPresentes[aux]=CAsCapac[aux];
                }
                if (CAsPresentes[aux]==0){
                    sobrevTotal[i]=0;
                    CAsPresentes[aux]=CAsCapac[aux];
                }
                if (CAsPresentes[aux]<0){
                    sobrevTotal[i]=0;
                    CAsPresentes[aux]=CAsCapac[aux]-(sqrt(pow(CAsPresentes[aux], 2)));
                }
                x[i]=CAsX[aux];
                y[i]=CAsY[aux];
            }
            else{
                sobra=sobra+sobrevTotal[i];
                sobrevTotal[i]=0;
            }
            menor=142;

        }
        if (robosX[i+1][1]==0&&robosY[i+1][1]==0){
            i=49;
        }
    }
    total=total+sobra;
    for (i=0;i<50;i++){
        total=total+CAsPresentes[i];
        fprintf(escreverAtendidos, "CA(%d,%d): Possui %d/%d sobreviventes.\n", CAsX[i],CAsY[i],CAsPresentes[i],CAsCapac[i]);
        if (CAsX[i+1]==0&&CAsY[i+1]==0){
            i=49;
        }
    }
    fprintf(escreverAtendidos,"\nForam salvos %d sobreviventes, mas não puderam ser alocados %d.", total, sobra);
    fclose(escreverAtendidos);
}



int main (){
    int robosId[50],robosX[50][30], robosY[50][30], robosSobrev [50][30], sobrevQnt[50], sobrevX[50], sobrevY[50], CAsX[50], CAsY[50], CAsCapac[50], sobrevTotal[50];
    float distanciaTotal[50], tempoTotal[50];
    dadosRobos(robosX,robosY,robosId);
    dadosCAs(CAsX, CAsY, CAsCapac);
    dadosSobreviventes(sobrevX, sobrevY, sobrevQnt);
    encontrarRoboProximo(robosX,robosY,sobrevX,sobrevY, robosSobrev);
    calcularDistanciaTotal(robosX,robosY,distanciaTotal);
    calcularTempoTotal(distanciaTotal, tempoTotal);
    arquivoTrajetos(robosId, robosX, robosY, robosSobrev, sobrevQnt, distanciaTotal, tempoTotal);
    arquivoHerois(robosId, robosSobrev, sobrevQnt, distanciaTotal, sobrevTotal);
    arquivoAtendidos(robosX, robosY, CAsX, CAsY, CAsCapac, sobrevTotal);
}
