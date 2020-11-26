#include "ArquivoPublicacoes.h"
#include "ExceptionFile.h"
#include "util/StringUtils.h"
#include "util/Tokenizer.h"

#include <string>
#include <iostream>
#include <fstream>
using namespace std;
using namespace cpp_util;

ArquivoPublicacoes::ArquivoPublicacoes(string pathname, vector<Docente*> docentes, vector<Veiculo*> veiculos ){
    this->entrada.open(pathname);
    if(!(this->entrada.is_open())){
        throw ExceptionFile();
    } else {
        this->docentes = docentes;
        this->veiculos = veiculos;
        loadDataToLocalMemory();
    }
}

void ArquivoPublicacoes::loadDataToLocalMemory() {
    string line;
    getline(this->entrada, line);
    while (getline(this->entrada, line)) {
        if (line != "") {

            cpp_util::Tokenizer splitter(line,';');
            vector<string> dados = splitter.remaining();
            for(unsigned i=0;i<dados.size();i++) {
                dados[i] = trim(dados[i]);
            }
            int ano = stoi(dados[0]);
            string siglaVeiculo = dados[1];
            string titulo = dados[2];
            int numero = stoi(dados[4]);
            int pgInicial = stoi(dados[7]);
            int pgFinal = stoi(dados[8]);

            // CRIAR EXCEÇÃO
            try {
                int isContained = 0;
                for(Veiculo* auxV : veiculos) {
                    if (auxV->getSigla().compare(siglaVeiculo)==0) {
                        isContained = 1;
                    }
                }
                if(isContained == 0) {
                    throw std::make_pair(siglaVeiculo,titulo);
                }
            } catch(std::pair<string,string> e) {
                ExceptionFile exc;
                exc.siglaVeiculoNaoDefinido(e.second,e.first);
                exit(1);
            }

            Veiculo* v = encontraVeiculo(siglaVeiculo);
            if(v==NULL) {
                //cout << "veiculo nulo" << endl;
            } else {
                Tokenizer autoresToken(dados[3],',');
                vector<string> codigoAutores = autoresToken.remaining();
                for(unsigned i=0;i<codigoAutores.size();i++) {
                    codigoAutores[i] = trim(codigoAutores[i]);
                }
                try {
                    for(string codigo : codigoAutores) {
                        int isDocContained = 0;
                        for (Docente *docente : docentes) {
                            if(docente->getCodigo().compare(codigo)==0) {
                                isDocContained = 1;
                            }
                        }
                        if(isDocContained == 0) {throw make_pair(titulo,codigo);}
                    }
                } catch (pair<string,string> e) {
                    ExceptionFile exceptionFile;
                    exceptionFile.docenteIndefinidoParaPublicacao(e.second,e.first);
                    exit(1);
                }
                vector<Docente*> autores = loadListaAutores(codigoAutores);
                if(dados[6].compare("") != 0) {
                    string local = dados[6];
                    Publicacao* publicacaoConferecia = new PublicacaoConferecia(numero, ano, pgInicial, pgFinal, titulo, v, local, autores);
                    publicacoes.push_back(publicacaoConferecia);
                    this->adicionarPubAoAutor(publicacaoConferecia, autores);
                }
                if(dados[5].compare("") != 0) {
                    int volume = stoi(dados[5]);
                    Publicacao* publicacaoPeriodico = new PublicacaoPeriodico(numero, ano, volume, pgInicial, pgFinal, titulo, v, autores);
                    publicacoes.push_back(publicacaoPeriodico);
                    this->adicionarPubAoAutor(publicacaoPeriodico, autores);
                }
            }
        }
    }
}

vector<Publicacao*> ArquivoPublicacoes::getPublicacoes() { return this->publicacoes; }

void ArquivoPublicacoes::adicionarPubAoAutor(Publicacao* p, vector<Docente*> autores) {
    for (Docente* autor : autores){
        for (Docente* docente : this->docentes){
            if (autor->getCodigo() == docente->getCodigo()){
                docente->adicionarPublicacao(p);
            }
        }
    }
}

vector<Docente*> ArquivoPublicacoes::loadListaAutores(vector<string> autores) {
    vector<Docente*> listaAutores;
    Docente *novoAutor;
    for(string codigo: autores) {
        novoAutor = encontraDocente(codigo);
        listaAutores.push_back(novoAutor);
    }

    return listaAutores;
}

Docente* ArquivoPublicacoes::encontraDocente(string codigo) {
    for (vector<Docente*>::iterator docente = this->docentes.begin(); docente != this->docentes.end();docente++){
        Docente *aux = *docente;
        if (aux->getCodigo().compare(codigo) == 0){
            return aux;
        }
    }
    return NULL;
}

Veiculo* ArquivoPublicacoes::encontraVeiculo(string sigla) {
    for(Veiculo* v: veiculos) {
        if(v->getSigla().compare(sigla) == 0) {
            return v;
        }
    }
    return NULL;
}