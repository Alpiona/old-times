/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Main.cpp
 * Author: alpio
 *
 * Created on 26 de Novembro de 2016, 16:56
 */
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "Leitor.h"
#include "EleicaoDeVereadores.h"
#include "Saida.h"
using namespace std;

int main(int argc, char* argv[]) {
    
    string line;
    ifstream arquivo (argv[1]);
    if (arquivo.is_open()) {
        Leitor *leitor = new Leitor();
        EleicaoDeVereadores *eleicao = new EleicaoDeVereadores();
        getline (arquivo,line) ;
        while (getline (arquivo,line))
        {
            leitor->pegaInformacaoDaLinha(line);
            eleicao->novoVereador(leitor);
        }
        eleicao->ordenaVereadoresPorVotos();
        eleicao->ordenaPartidosPorVotos();
        eleicao->ordenaColigacoesPorVotos();
        eleicao->vereadoresEleitos();
        eleicao->vereadoresMaisVotados();
        eleicao->seriamEleitosSeMajoritario();
        eleicao->foramEleitosMinoritario();
        eleicao->imprimeListaColigacoes();
        eleicao->imprimeListaPartidos();
    }

  else cout << "Não foi possível abrir o arquivo "<<argv[1]<<" .";    
    return 0;
}
