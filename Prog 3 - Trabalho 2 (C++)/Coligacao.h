/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Coligacao.h
 * Author: andre
 *
 * Created on 28 de Novembro de 2016, 21:01
 */

#ifndef COLIGACAO_H
#define COLIGACAO_H

#include "Partido.h"
#include "Coligacao.h"
#include <string>
#include <list>

class Partido;
class Coligacao {

private:
    std::string nome;
    std::list<Partido*> partidosDaColigacao;
    int votosColigacao, vereadoresEleitos;
public:
    void setNome (std::string nomeColigacao);
    std::string getNome ();
    void addNovoPartido (Partido* novoPartido);
    Partido getPartidosDaColigacao();
    void setVotosColigacao (int votosTotalColigacao);
    int getVotosColigacao ();
    void setVereadoresEleitos (int vereadoresTotalEleitos);
    int getVereadoresEleitos ();
    Coligacao();
    Coligacao(const Coligacao& orig);
    virtual ~Coligacao();

};

#endif /* COLIGACAO_H */

