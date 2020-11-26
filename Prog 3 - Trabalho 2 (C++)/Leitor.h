/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Leitor.h
 * Author: alpio
 *
 * Created on 27 de Novembro de 2016, 11:51
 */

#ifndef LEITOR_H
#define LEITOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "Leitor.h"

using namespace std;

class Leitor {
private:
    string nome, partido, coligacao, numero;
    bool eleito;
    int votos, id;
    
public:
    string getNomeVereador();
    string getPartido();
    string getColigacao();
    string getNumero();
    bool isEleito();
    int getVotos();
    int getId();
    void pegaInformacaoDaLinha (string dados);
    Leitor();
    Leitor(const Leitor& orig);
    virtual ~Leitor();

};

#endif /* LEITOR_H */

