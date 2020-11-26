/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Vereador.cpp
 * Author: alpio
 * 
 * Created on 26 de Novembro de 2016, 16:58
 */

#include<string>
#include "Partido.h"
#include "Vereador.h"

using namespace std;

void Vereador::setId (int numId){
    id = numId;
}

int Vereador::getId (){
    return id;
}

void Vereador::setColigacao (Coligacao* novaColigacao){
    coligacao = novaColigacao;
}

Coligacao* Vereador::getColigacao (){
    return coligacao;
}

void Vereador::setNome (std::string nom){
    nome = nom;
}

string Vereador::getNome (){
    return Vereador::nome;
}

void Vereador::setPartido(Partido* novoPartido){
    partido = novoPartido;
}

Partido* Vereador::getPartido (){
    return partido;
}

void Vereador::setVotos(int voto){
    votos = voto;
}

int Vereador::getVotos (){
    return votos;
}

void Vereador::setNum(std::string numero) {
    num = numero;
}

string Vereador::getNum (){
    return num;
}

void Vereador::setEleitos(bool eleit) {
    eleito = eleit;
}

bool Vereador::isEleito(){
    return eleito;
}

Vereador::Vereador() {
}

Vereador::Vereador(const Vereador& orig) {
}

Vereador::~Vereador() {
}

