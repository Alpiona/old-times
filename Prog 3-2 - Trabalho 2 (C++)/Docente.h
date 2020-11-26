#ifndef P3_T2_DOCENTE_H
#define P3_T2_DOCENTE_H

#include "Publicacao.h"
#include <string>

class Publicacao;

class Docente {
private:
    std::string codigo;
    std::string nome;
    time_t dataNascimento;
    time_t dataIngresso;
    bool coordenador;
    std::vector<Publicacao*> publicacoes;

public:
    Docente(std::string codigo, std::string nome, bool coordenador, time_t dataNascimento, time_t dataIngresso);
    void adicionarPublicacao(Publicacao *publicacao);
    std::string getCodigo();
    std::string getNome();
    std::vector<Publicacao*> getPublicacoes();
    time_t getDataIngresso();
    bool isCoordenador();
    bool lessThreeYears(time_t ano);
    bool isOverSixty(time_t ano);
};


#endif //P3_T2_DOCENTE_H
