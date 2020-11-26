#include <iostream>
#include "Veiculo.h"

using namespace std;

Veiculo::Veiculo(){}

Veiculo::Veiculo(string sigla, string nome, char tipo, double fatorDeImpacto, string ISSN) {
    this->sigla = sigla;
    this->nome = nome;
    this->tipo = tipo;
    this->fatorDeImpacto = fatorDeImpacto;
    this->ISSN = ISSN;
}

string Veiculo::getSigla() {return this->sigla;}
string Veiculo::getNome() {return this->nome;}
double Veiculo::getFatorImpacto() {return this->fatorDeImpacto;}
void Veiculo::addQualis(Qualis *qualis) {
    if(listaQualis.size() == 0) {
        this->listaQualis.push_back(qualis);
    }
}

char Veiculo::getTipo() {return this->tipo;}

vector<Qualis*> Veiculo::getListaQualis() {return this->listaQualis;}
