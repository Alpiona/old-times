#ifndef P3_T2_ARQUIVOQUALIFICACOES_H
#define P3_T2_ARQUIVOQUALIFICACOES_H

#include <string>
#include <fstream>
#include <iostream>
#include "Qualis.h"
#include "RegraPontuacao.h"
#include "Veiculo.h"

class Qualis;
class RegraPontuacao;
class Veiculo;
class ArquivoQualificacoes {
private:
    std::ifstream entrada;
    std::vector<Qualis*> qualificacoes;
    std::vector<Veiculo*> veiculos;
    std::vector<Veiculo*> novosVeiculos;
    RegraPontuacao* regra;
public:
    ArquivoQualificacoes(std::string pathname, std::vector<Veiculo*> veiculos);
    ArquivoQualificacoes(std::string pathname);
    void loadDataToLocalMemory();
    void setRegra(RegraPontuacao *regraPontuacao);
    Veiculo* encontraVeiculo(std::string aux);
    void colocarPontuacaoQualis();
    std::vector<Qualis*> getListaQualis();
};


#endif //P3_T2_ARQUIVOQUALIFICACOES_H
