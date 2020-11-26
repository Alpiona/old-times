#ifndef P3_T2_REGRAPONTUACAO_H
#define P3_T2_REGRAPONTUACAO_H

#include <array>
#include <string>
#include <vector>
#include "util/DateUtils.h"

class RegraPontuacao {
private:
    cpp_util::time_t dataInicio;
    cpp_util::time_t dataFinal;
    std::array<std::string,8> categoriasQualis;
    std::vector<int> pontuacaoQualis;
    double multiplicador;
    int qtdAnos;
    int pontuacaoMinima;

public:
    RegraPontuacao();
    RegraPontuacao(std::vector<int> pontuacaoQualis, double multiplicador, int qtdAnos, int pontuacaoMinima, time_t dataInicio, time_t dataFinal);
    int valorQualis(std::string qualis);
    std::string getAno();
    time_t getDataFinal();
    double getMultiplicador();
    int getQtdAnos();
    int getPontuacaoMinima();
};


#endif //P3_T2_REGRAPONTUACAO_H
