#ifndef P3_T2_VEICULO_H
#define P3_T2_VEICULO_H

#include <string>
#include <vector>
#include "Qualis.h"

class Veiculo {
private:
    std::string sigla;
    std::string nome;
    char tipo;
    double fatorDeImpacto;
    std::string ISSN;
    std::vector<Qualis*> listaQualis;

public:
    Veiculo();
    Veiculo(std::string sigla, std::string nome, char tipo, double fatorDeImpacto, std::string ISSN);
    std::string getSigla();
    std::string getNome();
    double getFatorImpacto();
    void addQualis(Qualis* qualis);
    std::vector<Qualis*> getListaQualis();
    char getTipo();
};


#endif //P3_T2_VEICULO_H
