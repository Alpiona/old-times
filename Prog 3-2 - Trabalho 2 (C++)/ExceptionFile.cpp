#include "ExceptionFile.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;
ExceptionFile::ExceptionFile() {}
const string ExceptionFile::errorMessage() const {
    return this->message;
}

void ExceptionFile::docenteRepetido(string codigo) {
    cout<<"Código repetido para docente: "<<codigo<<"."<<endl;
    exit(0);
}

void ExceptionFile::docenteIndefinidoParaPublicacao(string codigo, string titulo) {
    cout <<"Código de docente não definido usado na publicação \"" << titulo << "\": " << codigo << "." << endl;
    exit(0);
}

void ExceptionFile::veiculoRepetido(string ISSN) {
    cout <<"Código repetido para veículo: " << ISSN << "." << endl;
    exit(0);
}

void ExceptionFile::qualisDesconhecido(string vSigla, int ano, string qualis) {
    cout << "Qualis desconhecido para qualificação do veículo " << vSigla << " no ano " << ano << ": " << qualis << "." << endl;
    exit(0);
}

void ExceptionFile::qualisDesconhecidoParaRegra(string ano, string qualis) {
    cout << "Qualis desconhecido para regras de " << ano << ": " << qualis << endl;
    exit(0);
}

void ExceptionFile::siglaVeiculoNaoDefinido(string titulo, string sigla) {
    cout << "Sigla de veículo não definida usada na publicação \"" << titulo << "\": " << sigla << "." << endl;
    exit(0);
}

void ExceptionFile::siglaVeiculoNaoDefinidaQualificacao(int ano, string sigla) {
    cout << "Sigla de veículo não definida usada na qualificação do ano \"" << ano << "\": " << sigla << "." << endl;
    exit(0);
}

void ExceptionFile::tipoVeiculoNaoDefinido(string sigla, char tipo) {
    cout << "Tipo de veículo desconhecido para veículo " << sigla << ": " << tipo << "." << endl;
    exit(0);
}
