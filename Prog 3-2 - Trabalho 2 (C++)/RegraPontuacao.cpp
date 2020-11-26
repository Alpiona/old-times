#include <iostream>
#include "RegraPontuacao.h"
#include "util/DateUtils.h"

using namespace std;
using namespace cpp_util;


RegraPontuacao::RegraPontuacao() {}

RegraPontuacao::RegraPontuacao(vector<int> pontuacaoQualis, double multiplicador, int qtdAnos, int pontuacaoMinima,
                               time_t dataInicio, time_t dataFinal) {
    this->categoriasQualis = {"A1", "A2", "B1", "B2", "B3", "B4", "B5", "C"};
    this->dataInicio = dataInicio;
    this->dataFinal = dataFinal;
    this->pontuacaoQualis = pontuacaoQualis;
    this->multiplicador = multiplicador;
    this->qtdAnos = qtdAnos;
    this->pontuacaoMinima = pontuacaoMinima;
}

string RegraPontuacao::getAno() {
    string dInicio = formatDate(this->dataInicio,DATE_FORMAT_PT_BR_SHORT);
    string ano = dInicio.substr(6,9);
    return ano;
}

time_t RegraPontuacao::getDataFinal(){return this->dataFinal;}

int RegraPontuacao::valorQualis(string qualis) {
    for (int i =0; i<8; i++){
        if (this->categoriasQualis[i].compare(qualis) == 0){
            return (pontuacaoQualis[i]);
        }
    }
    return 0;
}

double RegraPontuacao::getMultiplicador() {return this->multiplicador;}
int RegraPontuacao::getQtdAnos() {return this->qtdAnos;}

int RegraPontuacao::getPontuacaoMinima() {return this->pontuacaoMinima;}
