
#include "Coligacao.h"
#include "Partido.h"
#include "Vereador.h"
#include <string>


using namespace std;

void Coligacao::setNome (string nomeColigacao){
    nome = nomeColigacao;
}

string Coligacao::getNome (){
    return nome;
}

void Coligacao::addNovoPartido (Partido* novoPartido){
    partidosDaColigacao.push_back(novoPartido);
}

void Coligacao::setVotosColigacao (int votosTotalColigacao){
    votosColigacao = votosTotalColigacao;
}

int Coligacao::getVotosColigacao (){
    return votosColigacao;
}

void Coligacao::setVereadoresEleitos (int vereadoresTotalEleitos){
    vereadoresEleitos = vereadoresTotalEleitos;
}

int Coligacao::getVereadoresEleitos (){
    return vereadoresEleitos;
}

Coligacao::Coligacao() {
}

Coligacao::Coligacao(const Coligacao& orig) {
}

Coligacao::~Coligacao() {
}

