/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EleicaoDeVereadores.h
 * Author: andre
 *
 * Created on 28 de Novembro de 2016, 21:01
 */


#ifndef ELEICAODEVEREADORES_H
#define ELEICAODEVEREADORES_H

#include <list>
#include <string>
#include "EleicaoDeVereadores.h"
#include "Leitor.h"
#include "Partido.h"
#include "Vereador.h"
#include "Coligacao.h"

class Vereador;
class Coligacao;
class Partido;
class Leitor;
class EleicaoDeVereadores {
private:
    std::list<Vereador*> listaTodosOsVereadores;
    std::list<Coligacao*> listaTodasAsColigacoes;
    std::list<Partido*> listaTodosOsPartidos;
    int votosTotais, eleitos;
public:
    void novoVereador (Leitor *leitor);
    Partido* criaPartido (Leitor* leitor);
    Partido* verificaPartido (Leitor *leitor);
    Coligacao* criaColigacao (Leitor* leitor);
    Coligacao* verificaColigacao (Leitor* leitor);
    void adicionaColigacoesDeUmPartido ();
    void setListaVereadores (list<Vereador*> listaVereadores);
    
    EleicaoDeVereadores();
    EleicaoDeVereadores(const EleicaoDeVereadores& orig);
    virtual ~EleicaoDeVereadores();
    void teste();
    
    void ordenaVereadoresPorVotos ();
    void ordenaPartidosPorVotos();
    void ordenaColigacoesPorVotos();

    void vereadoresEleitos();
    void vereadoresMaisVotados();
    void seriamEleitosSeMajoritario(); 
    void foramEleitosMinoritario();
    void imprimeListaColigacoes();
    void imprimeListaPartidos();
};

#endif /* ELEICAODEVEREADORES_H */

