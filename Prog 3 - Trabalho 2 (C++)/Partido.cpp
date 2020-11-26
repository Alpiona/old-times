/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Partido.cpp
 * Author: andre
 * 
 * Created on 28 de Novembro de 2016, 21:01
 */

#include <string>
#include <list>
#include "Coligacao.h"
#include "Partido.h"
#include "Vereador.h"

using namespace std;

void Partido::setColigacao (Coligacao* novaColigacao){
    coligacao = novaColigacao;
}

Coligacao* Partido::getColigacao (){
    return coligacao;
}

void Partido::setNome (string nomePartido){
    nome = nomePartido;
}

string Partido::getNome(){
    return nome;
}

void Partido::addNovoVereador (Vereador* novoVereador){
    vereadoresDoPartido.push_back(novoVereador);
}

void Partido::setVotosPartido (int votosTotalPartido){
    votosPartido = votosTotalPartido;
}

int Partido::getVotosPartido (){
    return votosPartido;
}

void Partido::setVereadoresEleitos (int vereadoresTotalEleitos){
    vereadoresEleitos = vereadoresTotalEleitos;
}

int Partido::getVereadoresEleitos (){
    return vereadoresEleitos;
}

Partido::Partido() {
}

Partido::Partido(const Partido& orig) {
}

Partido::~Partido() {
}

