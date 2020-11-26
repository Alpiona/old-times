#ifndef P3_T2_QUALIS_H
#define P3_T2_QUALIS_H

#include <string>
#include <array>
#include "RegraPontuacao.h"

class Qualis {
private:
    int ano;
    int pontuacao;
    std::string qualis;
    std::string siglaVeiculo;
    std::array<std::string,8> categoriasQualis;
    std::vector<std::string> todosQualis = {"A1", "A2", "B1", "B2", "B3", "B4", "B5", "C"};;
    RegraPontuacao *regra;

public:
    Qualis(int ano, std::string qualis, std::string siglaVeiculo);
    void setRegra (RegraPontuacao *regra);
    std::string getQualis();
    void setPontuacao(int pontuacao);
    std::string getSiglaVeiculo();
    int getPontuacao();
    int getAno();
    bool isValidQualis();
};


#endif //P3_T2_QUALIS_H
