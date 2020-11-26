/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Vereador.h
 * Author: alpio
 *
 * Created on 26 de Novembro de 2016, 16:58
 */

#ifndef VEREADOR_H
#define VEREADOR_H

#include "Partido.h"
#include "Coligacao.h"

class Partido;
class Coligacao;
class Vereador {
private:
    Partido* partido;
    Coligacao* coligacao;
    std::string nome, num;
    int id, votos;
    bool eleito;	
    
public:
    void setId (int id);
    int getId();
    void setColigacao (Coligacao* novaColigacao);
    Coligacao* getColigacao ();
    void setNome (std::string nom);
    std::string getNome ();
    void setPartido (Partido* novoPartido);
    Partido* getPartido ();
    void setNum (std::string numero);
    std::string getNum ();
    void setVotos (int voto);
    int getVotos ();
    void setEleitos (bool eleit);
    bool isEleito ();
    Vereador();
    Vereador(const Vereador& orig);
    virtual ~Vereador();


};

#endif /* VEREADOR_H */

