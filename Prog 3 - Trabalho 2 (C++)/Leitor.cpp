/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Leitor.cpp
 * Author: alpio
 * 
 * Created on 27 de Novembro de 2016, 11:51
 */
#include <iostream>
#include<locale>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "Leitor.h"

using namespace std;

void Leitor::pegaInformacaoDaLinha(string dados){
    char letra = dados[0];
    string aux;
    if (letra == '*'){
        eleito = true;
        dados.erase(0,1);
    }
    else if (letra == '#'){
        eleito = false;
        dados.erase(0,1);
    }
    else {
        eleito = false;
    }
    
    string separa = ";";
    size_t pos = 0;
    pos = dados.find(separa);
    aux = dados.substr(0, pos);
    id = atoi(aux.c_str());
    dados.erase(0,pos+1);
    
    pos = dados.find(separa);
    numero = dados.substr(0, pos);
    dados.erase(0,pos+1);
    
    pos = dados.find(separa);
    nome = dados.substr(0, pos);
    dados.erase(0,pos+1);   
    
    pos = dados.find(separa);
    aux = dados.substr(0, pos);
    dados.erase(0,pos+1);
    if (aux.find("-")!=aux.npos){
        pos = aux.find("-");
        partido = aux.substr(0,pos-1);
        aux.erase(0,pos+2);
        coligacao = aux;
    }
    else{
        partido = aux;
        coligacao.clear();
    } 

    pos = dados.find(separa);
    aux = dados.substr(0, pos);
    /*locale brasilLocale ("pt_BR.UTF-8");
    istringstream input (aux);
    input.imbue(brasilLocale);                      //O aux retira a parte com os votos, retirando da posição 0 até a posição do ponto e virgula (pos). Após isso
    input>>votos;*/                                 //é verificado a presença de ponto no número (com 4+ dígitos) e deleta o ponto. Porém por algum motivo, números
    if (aux.find(".")!=aux.npos){                   //com mais de 4 dígitos são convertidos para números de 4 digitos, isso ocorre ainda dentro da string aux, não
    pos = aux.find(".");                            //foi encontrada uma solução.
    aux.erase(pos,pos);
    }                                               //Com o método de locale pt_BR (ainda no código, porém desativado), isso não ocorre, porém quando sai dessa função,
    votos = atoi(aux.c_str());                      //ao chegar na função que ordena pela quantidade de votos, ocorre erro durante a comparação e não funciona
    return;                                         //como deveria, mesmo que ambos os métodos fazem 'votos' sairem como int dessa função. Por isso ficou o método anterior.
}

string Leitor::getNomeVereador() {
    return nome;
}

string Leitor::getPartido() {
    return partido;
}

string Leitor::getColigacao() {
    return coligacao;
}

bool Leitor::isEleito() {
    return eleito;
}

int Leitor::getVotos() {
    return votos;
}

int Leitor::getId() {
    return id;
}

string Leitor::getNumero() {
    return numero;
}

Leitor::Leitor() {

}

Leitor::Leitor(const Leitor& orig) {
}

Leitor::~Leitor() {
}

