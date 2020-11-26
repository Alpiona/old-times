/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Partido.h
 * Author: andre
 *
 * Created on 28 de Novembro de 2016, 21:01
 */

#ifndef PARTIDO_H
#define PARTIDO_H

#include <string>
#include <list>
#include "Coligacao.h"
#include "Partido.h"
#include "Vereador.h"

class Coligacao;
class Vereador;
class Partido {
    
private:
    Coligacao* coligacao;
    std::string nome;
    std::list<Vereador*> vereadoresDoPartido;
    int votosPartido, vereadoresEleitos;
public:
    void setColigacao (Coligacao* novaColigacao);
    Coligacao* getColigacao ();
    void setNome (std::string nomePartido);
    std::string getNome();
    void addNovoVereador (Vereador* novoVereador);
    Vereador* getListaVereador ();
    void setVotosPartido (int votosTotalPartido);
    int getVotosPartido ();
    void setVereadoresEleitos (int vereadoresTotalEleitos);
    int getVereadoresEleitos ();
    Partido();
    Partido(const Partido& orig);
    virtual ~Partido();

};

#endif /* PARTIDO_H */

