//
// Created by Sandor ferreira da silva on 27/07/17.
//

#include "RelatorioPublicacao.h"
#include <fstream>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <iomanip>

RelatorioPublicacao::RelatorioPublicacao(string pathname, vector<Publicacao*> publicacoes) {
    this->pathname = pathname;
    this->publicacoes = publicacoes;
}

vector<Publicacao *> RelatorioPublicacao::ordenarPorQualis(string qualis) {
    vector<Publicacao*> auxPub;
    for (Publicacao* auxPublicacao : publicacoes) {
        if (auxPublicacao->getQualis().compare(qualis) == 0) {
            auxPub.push_back(auxPublicacao);
        }
    }
    return auxPub;
}

int RelatorioPublicacao::getMaiorAno(vector<Publicacao *> auxPubs) {
    int maiorAno = 0;

    for (Publicacao* auxPub : auxPubs) {
        maiorAno = auxPub->getAno();
        break;
    }
    for (Publicacao* auxPublicacao : auxPubs) {
        if (auxPublicacao->getAno() >= maiorAno) {
            maiorAno = auxPublicacao->getAno();
        }
    }
    return maiorAno;
}

vector<Publicacao *> RelatorioPublicacao::ordenarPorAno(int maiorAno, int ano, vector<Publicacao *> pubPorQualis) {
    vector<Publicacao*> auxSiglas;
    for(Publicacao* auxPub : pubPorQualis) {
        if(auxPub->getAno() == ano) {
            auxSiglas.push_back(auxPub);
        }
    }
    auxSiglas = this->ordenarPorSigla(auxSiglas);

    return auxSiglas;
}

vector<Publicacao *> RelatorioPublicacao::ordenarPorSigla(vector<Publicacao *> auxPubs) {
    vector<Publicacao*> returnedSiglaAndTitulo;
    vector<string> auxSiglasString;
    for(Publicacao* auxPub: auxPubs) {
        bool tem = false;
        if (auxSiglasString.empty()){
            auxSiglasString.push_back(auxPub->getVeiculo()->getSigla());
        }
        else {
            for (string auxString : auxSiglasString){
                if (auxString.compare(auxPub->getVeiculo()->getSigla())==0){
                    tem = true;
                }
            }
            if (!tem){
                auxSiglasString.push_back(auxPub->getVeiculo()->getSigla());
            }
        }
    }
    sort(begin(auxSiglasString), end(auxSiglasString));//this->getSortedStringArray(auxSiglasString);
    for(string sigla : auxSiglasString) {
        vector<Publicacao*> auxSiglasHS;
        for(Publicacao* auxPub : auxPubs) {
            if(auxPub->getVeiculo()->getSigla().compare(sigla) == 0) {
                auxSiglasHS.push_back(auxPub);
            }
        }

        vector<Publicacao*> vetorTituloOrdenado;
        vector<string> titulos;
        for(Publicacao* auxPublicacaoTitulo: auxSiglasHS) {
            titulos.push_back(auxPublicacaoTitulo->getNome());
        }
        sort(begin(titulos), end(titulos));
        //cout << titulos << endl;
        //titulos = RelatorioPublicacao::getSortedStringArray(titulos);
        for(string titulo : titulos) {
            for(Publicacao* auxPub : auxSiglasHS) {
                if(titulo.compare(auxPub->getNome()) == 0) {
                    vetorTituloOrdenado.push_back(auxPub);
                    break;
                }
            }
        }
        for(Publicacao* okok : vetorTituloOrdenado) {
            returnedSiglaAndTitulo.push_back(okok);
        }
    }

    return returnedSiglaAndTitulo;
}

vector<string> RelatorioPublicacao::getSortedStringArray(vector<string> array) {
    sort(begin(array),end(array));
    return array;
}

vector<Publicacao *> RelatorioPublicacao::ordenar() {
    vector<Publicacao*> listaOrdenada;
    for(unsigned i=0;i<this->publicacoes.size();i++) {
        vector<Qualis *> qualisPossiveis = this->publicacoes[i]->getVeiculo()->getListaQualis();;
        if (qualisPossiveis.size() == 0) {
            cout << "Qualis vazia" << endl;
        }
        for(unsigned y=0;y<qualisPossiveis.size();y++) {
          if (qualisPossiveis.at(y)->getAno() <= this->publicacoes.at(i)->getAno()){
            this->publicacoes.at(i)->setQualis(qualisPossiveis.at(y)->getQualis());
          }
        }
    }
    for(string categoriaQualis: categoriasQualis) {
        vector<Publicacao*> auxPubs;
        vector<Publicacao*> pubPorQualis = this->ordenarPorQualis(categoriaQualis);
        int maiorAno = this->getMaiorAno(pubPorQualis);
        for(int ano = maiorAno; ano > 2000; ano--) {
            vector<Publicacao*> ordenadoPorAno = this->ordenarPorAno(maiorAno, ano, pubPorQualis);
            for(Publicacao* okok: ordenadoPorAno) {
                auxPubs.push_back(okok);
            }
        }
        for(Publicacao* okok: auxPubs) {
            listaOrdenada.push_back(okok);
        }
    }

    return listaOrdenada;
}

void RelatorioPublicacao::write() {
    vector<Publicacao*> pOrdenadas = this->ordenar();

    ofstream relatorioCSV;
    locale mylocale("pt_BR.UTF-8");
    relatorioCSV.imbue(mylocale);
    relatorioCSV.open(pathname);
    if(!relatorioCSV.is_open()) {
        cout << "Não criou" << endl;
    }

    relatorioCSV << FILE_HEDER << endl;
    for(Publicacao* p: pOrdenadas) {
        relatorioCSV << to_string(p->getAno()) << ";" << p->getVeiculo()->getSigla() << ";" << p->getVeiculo()->getNome() << ";";
        relatorioCSV << p->getQualis() << ";" << setprecision(3) << fixed << p->getVeiculo()->getFatorImpacto() << ";" << p->getNome() << ";";
        int sizeAutores = p->getAutores().size();
        if(sizeAutores == 1) {
            relatorioCSV << p->getAutores()[0]->getNome() << '\n';
        } else {
            int iterador = 0;
            for(Docente* d: p->getAutores()) {
                if(iterador != sizeAutores-1) {
                    relatorioCSV << d->getNome() << ",";
                } else {
                    relatorioCSV << d->getNome() << '\n';
                }
                iterador++;
            }
        }
    }
}
