#ifndef P3_T2_ARQUIVOVEICULO_H
#define P3_T2_ARQUIVOVEICULO_H

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include "Veiculo.h"

class ArquivoVeiculo {
private:
    std::vector<Veiculo*> veiculos;
    std::ifstream entrada;

public:
    ArquivoVeiculo(std::string pathname);
    std::vector<Veiculo*> getVeiculos();
    void loadDataToMemory();
};


#endif //P3_T2_ARQUIVOVEICULO_H
