#include "Qualis.h"

using namespace std;

Qualis::Qualis(int ano, string qualis, string sigla) {
    this->ano = ano;
    this->qualis = qualis;
    this->siglaVeiculo = sigla;
}

void Qualis::setRegra(RegraPontuacao *regra) {this->regra = regra;}
void Qualis::setPontuacao(int pontuacao) {this->pontuacao = pontuacao;}

string Qualis::getQualis() {
    return this->qualis;
}

int Qualis::getPontuacao() {
    return this->pontuacao;
}

string Qualis::getSiglaVeiculo() {
    return this->siglaVeiculo;
}

int Qualis::getAno() { return this->ano; }

bool Qualis::isValidQualis() {
    bool isContained = false;
    for(string qualis : todosQualis) {
        if(this->qualis.compare(qualis)==0) {
            isContained = true;
        }
    }
    return isContained;
}