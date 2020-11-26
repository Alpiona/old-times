#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "ArquivoDocente.h"
#include "ArquivoPublicacoes.h"
#include "ArquivoQualificacoes.h"
#include "Docente.h"
#include "Publicacao.h"
#include "ArquivoRegras.h"
#include "ArquivoVeiculo.h"
#include "ExceptionFile.h"
#include "RelatorioPublicacao.h"
#include "RelatorioEstatisticas.h"
#include "RelatorioRecredenciamento.h"
#include "Argumento.h"

using namespace std;

// ios::binary - treating the file as binary

vector<Docente*> docentes;
vector<Publicacao*> publicacoes;
vector<Qualis*> listaQualis;
vector<Veiculo*> veiculos;
RegraPontuacao* regra;



int main(int argc, char* argv[]) {


    Argumento* argumento = new Argumento(argc, argv);
    ExceptionFile e;
    ArquivoDocente *arqDocente;
    ArquivoVeiculo *arqVeiculo;
    ArquivoPublicacoes *arqPublicacoes;
    ArquivoQualificacoes *arqQualificacoes; // implementar getQualificacoes
    ArquivoRegras *arqRegras; // implementar getRegra

    try {
        arqDocente = new ArquivoDocente(argumento->get("-d"));
        docentes = arqDocente->getDocentes();
    } catch (ExceptionFile e) {
        cout << e.errorMessage() << endl;
    }

    try {
        arqVeiculo = new ArquivoVeiculo(argumento->get("-v"));
        veiculos = arqVeiculo->getVeiculos();
    } catch( ExceptionFile e) {
        cout << e.errorMessage() << endl;
    }


    try {
        arqPublicacoes = new ArquivoPublicacoes(argumento->get("-p"), docentes, veiculos);
        publicacoes = arqPublicacoes->getPublicacoes();
    } catch (ExceptionFile e) {
        cout << e.errorMessage() << endl;
    }

    try {
        arqRegras = new ArquivoRegras(argumento->get("-r"));
        regra = arqRegras->getRegra(argumento->get("-a"));
    } catch(ExceptionFile e) {
        cout << e.errorMessage() << endl;
    }

    try {
        arqQualificacoes = new ArquivoQualificacoes(argumento->get("-q"), veiculos);
        arqQualificacoes->setRegra(regra);
        listaQualis = arqQualificacoes->getListaQualis();
    } catch(ExceptionFile e) {
        cout << e.errorMessage() << endl;
    }



    //cout << "gente???" << endl;


    //Gerando Relatórios



    RelatorioPublicacao* relatorioPublicacao = new RelatorioPublicacao("2-publicacoes.csv", publicacoes);
    relatorioPublicacao->write();

    RelatorioEstatisticas* relatorioEstatisticas = new RelatorioEstatisticas("3-estatisticas.csv", publicacoes);
    relatorioEstatisticas->write();

    RelatorioRecredenciamento* relatorioRecredenciamento = new RelatorioRecredenciamento("1-recredenciamento.csv", docentes, regra, listaQualis);
    relatorioRecredenciamento->write();

    return 0;
}
