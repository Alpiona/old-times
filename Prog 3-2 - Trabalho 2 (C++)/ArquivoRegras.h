#ifndef P3_T2_ARQUIVOREGRAS_H
#define P3_T2_ARQUIVOREGRAS_H

#include "RegraPontuacao.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class RegraPontuacao;
class ArquivoRegras {
private:
    std::ifstream entrada;
    std::vector<RegraPontuacao*> regras;
    std::vector<std::string> todosQualis = {"A1", "A2", "B1", "B2", "B3", "B4", "B5", "C"};

public:
    ArquivoRegras(std::string pathname);
    RegraPontuacao* getRegra(std::string ano);
    void loadDataToMemory();
    void addRegra(RegraPontuacao* regraPontuacao);
};


#endif //P3_T2_ARQUIVOREGRAS_H
