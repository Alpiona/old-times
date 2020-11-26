
#include <list>
#include <string>
#include <iostream>
#include "EleicaoDeVereadores.h"
#include "Leitor.h"
#include "Partido.h"
#include "Vereador.h"
#include "Coligacao.h"

using namespace std;

void EleicaoDeVereadores::novoVereador (Leitor *leitor){
    Vereador *novoVereador = new Vereador;
    novoVereador->setId(leitor->getId());
    novoVereador->setNome(leitor->getNomeVereador());
    novoVereador->setNum(leitor->getNumero());
    novoVereador->setVotos(leitor->getVotos());
    novoVereador->setEleitos(leitor->isEleito());
    Partido *partido = verificaPartido(leitor);
    novoVereador->setPartido(partido);
    novoVereador->setColigacao(partido->getColigacao());
    partido->addNovoVereador(novoVereador);					
    listaTodosOsVereadores.push_back(novoVereador);
    if (leitor->isEleito()){
        eleitos+=1;
    }
}

Partido* EleicaoDeVereadores::criaPartido (Leitor* leitor){
    Partido *novoPartido = new Partido;
    novoPartido->setNome(leitor->getPartido());
    novoPartido->setVotosPartido(leitor->getVotos());
    if (leitor->isEleito()){
        novoPartido->setVereadoresEleitos(1);
    }
    return novoPartido;
}

Partido* EleicaoDeVereadores::verificaPartido (Leitor *leitor){
    bool existePartido=false;
    Partido *novoPartido = new Partido();
    for (list<Partido*>::iterator partido = listaTodosOsPartidos.begin(); partido != listaTodosOsPartidos.end(); partido++){
        Partido *aux = *partido;
        if (leitor->getPartido().compare(aux->getNome()) == 0){
            existePartido=true;
            aux->setVotosPartido(aux->getVotosPartido()+leitor->getVotos());
            if (leitor->isEleito()){
                aux->setVereadoresEleitos(aux->getVereadoresEleitos()+1);
            }
            Coligacao *coligacao = verificaColigacao(leitor);
            *partido = aux;
            return *partido;										
        }
    }
    if (!(existePartido)){
        novoPartido = criaPartido(leitor);
        listaTodosOsPartidos.push_back(novoPartido);
        Coligacao *coligacao = new Coligacao;
        coligacao = verificaColigacao(leitor);
        coligacao->addNovoPartido(novoPartido);	
        novoPartido->setColigacao(coligacao);
    }
    return novoPartido;
}

Coligacao* EleicaoDeVereadores::criaColigacao (Leitor* leitor){
    Coligacao* novaColigacao = new Coligacao;
    if (!leitor->getColigacao().compare("")==0){
        novaColigacao->setNome(leitor->getColigacao());
    }
    else{
        novaColigacao->setNome(leitor->getPartido());
    }
    novaColigacao->setVotosColigacao(leitor->getVotos());
    novaColigacao->addNovoPartido(criaPartido(leitor));
    if (leitor->isEleito()){
        novaColigacao->setVereadoresEleitos(1);
    }
    return novaColigacao;
}

Coligacao* EleicaoDeVereadores::verificaColigacao (Leitor* leitor){
    bool existeColigacao = false;
    Coligacao* novaColigacao = new Coligacao;
    for (list <Coligacao*>::iterator coligacao = listaTodasAsColigacoes.begin(); coligacao!=listaTodasAsColigacoes.end(); coligacao++){
        Coligacao *aux = *coligacao;
        if (!leitor->getColigacao().compare("")==0){
            if (leitor->getColigacao().compare(aux->getNome())==0){
                existeColigacao = true;
                aux->setVotosColigacao(aux->getVotosColigacao()+leitor->getVotos());
                if (leitor->isEleito()){
                    aux->setVereadoresEleitos(aux->getVereadoresEleitos()+1);
                }
                *coligacao = aux;
                return *coligacao;
            }
        }
        else {
            if (leitor->getPartido().compare(aux->getNome())==0){
                existeColigacao = true;
                aux->setVotosColigacao(aux->getVotosColigacao()+leitor->getVotos());
                if (leitor->isEleito()){
                    aux->setVereadoresEleitos(aux->getVereadoresEleitos()+1);
                }
                *coligacao = aux;
                return *coligacao;
            }
        }
    }
    if (!(existeColigacao)){
        novaColigacao = criaColigacao(leitor);
        listaTodasAsColigacoes.push_back(novaColigacao);
    }
    return novaColigacao;    
}

void EleicaoDeVereadores::ordenaVereadoresPorVotos(){
    Vereador *vereadorMaisVotado = new Vereador();
    list<Vereador*> vereadoresOrdenados;
    list<Vereador*>::iterator it;
    bool listaIncompleta = true;
    while (listaIncompleta){												
        listaIncompleta = false;										
        for (list<Vereador*>::iterator vereador = listaTodosOsVereadores.begin(); vereador != listaTodosOsVereadores.end(); vereador++){
            Vereador *auxVereador = *vereador;
            if (vereadorMaisVotado->getVotos()<=auxVereador->getVotos()){
                it = vereador;
                vereadorMaisVotado = auxVereador;								
                listaIncompleta=true;								
            }															
        }
        if (listaIncompleta){
            votosTotais += vereadorMaisVotado->getVotos();
            vereadoresOrdenados.push_back(vereadorMaisVotado);
            it = listaTodosOsVereadores.erase(it);
            vereadorMaisVotado = new Vereador();
        }														
    }
    listaTodosOsVereadores = vereadoresOrdenados;
}

void EleicaoDeVereadores::ordenaPartidosPorVotos(){
    Partido *partidoMaisVotado = new Partido();
    list<Partido*> partidosOrdenados;
    list<Partido*>::iterator it;
    bool listaIncompleta = true;
    while (listaIncompleta){											
        listaIncompleta = false;									
        for (list<Partido*>::iterator partido = listaTodosOsPartidos.begin(); partido != listaTodosOsPartidos.end(); partido++){
            Partido *auxPartido = *partido;
            if (partidoMaisVotado->getVotosPartido()<=auxPartido->getVotosPartido()){
                it = partido;
                partidoMaisVotado = auxPartido;								
                listaIncompleta=true;									
            }														
        }
        if (listaIncompleta){
            partidosOrdenados.push_back(partidoMaisVotado);
            it = listaTodosOsPartidos.erase(it);
            partidoMaisVotado = new Partido();
        }														
    }
    listaTodosOsPartidos = partidosOrdenados;
}

void EleicaoDeVereadores::ordenaColigacoesPorVotos(){
    Coligacao *coligacaoMaisVotada = new Coligacao();
    list<Coligacao*> coligacoesOrdenadas;
    list<Coligacao*>::iterator it;
    bool listaIncompleta = true;
    while (listaIncompleta){											
        listaIncompleta = false;									
        for (list<Coligacao*>::iterator coligacao = listaTodasAsColigacoes.begin(); coligacao != listaTodasAsColigacoes.end(); coligacao++){
            Coligacao *auxColigacao = *coligacao;
            if (coligacaoMaisVotada->getVotosColigacao()<=auxColigacao->getVotosColigacao()){
                it = coligacao;
                coligacaoMaisVotada = auxColigacao;								
                listaIncompleta=true;										
            }														
        }
        if (listaIncompleta){
            coligacoesOrdenadas.push_back(coligacaoMaisVotada);
            it = listaTodasAsColigacoes.erase(it);
            coligacaoMaisVotada = new Coligacao();
        }														
    }
    listaTodasAsColigacoes = coligacoesOrdenadas;
}

void EleicaoDeVereadores::vereadoresEleitos(){
    cout<<"Vereadores eleitos:"<<endl;
    for (list<Vereador*>::iterator vereador = listaTodosOsVereadores.begin(); vereador != listaTodosOsVereadores.end(); vereador++){
        Vereador *auxVereador = *vereador;
        if (auxVereador->isEleito()){
            if (auxVereador->getColigacao()->getNome().compare(auxVereador->getPartido()->getNome())==0){
                cout<<auxVereador->getId()<<" - "<<auxVereador->getNome()<<" ("<<auxVereador->getPartido()->getNome()<<", "<<auxVereador->getVotos()<<" votos)"<<endl;	
            }
            else{
                cout<<auxVereador->getId()<<" - "<<auxVereador->getNome()<<" ("<<auxVereador->getPartido()->getNome()<<", "<<auxVereador->getVotos()<<" votos) - Coligação: "<<auxVereador->getColigacao()->getNome()<<endl;
            }
        }
    }
    cout<<endl;
}

void EleicaoDeVereadores::vereadoresMaisVotados(){
    int i=0;
    cout<<"Candidatos mais votados (em ordem decrescente de votação e respeitando número de vagas):"<<endl;
    for (list<Vereador*>::iterator vereador = listaTodosOsVereadores.begin(); vereador != listaTodosOsVereadores.end(); vereador++){
        Vereador *auxVereador = *vereador;
        if (i<eleitos){
            i+=1;
            if (auxVereador->getColigacao()->getNome().compare(auxVereador->getPartido()->getNome())==0){
                cout<<i<<" - "<<auxVereador->getNome()<<" ("<<auxVereador->getPartido()->getNome()<<", "<<auxVereador->getVotos()<<" votos)"<<endl;	
            }														
            else{
                cout<<i<<" - "<<auxVereador->getNome()<<" ("<<auxVereador->getPartido()->getNome()<<", "<<auxVereador->getVotos()<<" votos) - Coligação: "<<auxVereador->getColigacao()->getNome()<<endl;
            }
        }
    }
    cout<<endl;
}

void EleicaoDeVereadores::seriamEleitosSeMajoritario(){
    int i=0;
    cout<<"Teriam sido eleitos se a votação fosse majoritária, e não foram eleitos:"<<endl<<"(com sua posição no ranking de mais votados)"<<endl;
    for (list<Vereador*>::iterator vereador = listaTodosOsVereadores.begin(); vereador != listaTodosOsVereadores.end(); vereador++){
        Vereador *auxVereador = *vereador;
        if (i<eleitos){
            i+=1;
            if (!(auxVereador->isEleito())){
                if (auxVereador->getColigacao()->getNome().compare(auxVereador->getPartido()->getNome())==0){
                    cout<<i<<" - "<<auxVereador->getNome()<<" ("<<auxVereador->getPartido()->getNome()<<", "<<auxVereador->getVotos()<<" votos)"<<endl;	
                }														
                else{
                    cout<<i<<" - "<<auxVereador->getNome()<<" ("<<auxVereador->getPartido()->getNome()<<", "<<auxVereador->getVotos()<<" votos) - Coligação: "<<auxVereador->getColigacao()->getNome()<<endl;
                }
            }
        }
    }
    cout<<endl;
}

void EleicaoDeVereadores::foramEleitosMinoritario(){
    int i=0;
    cout<<"Eleitos, que se beneficiaram do sistema proporcional:"<<endl<<"(com sua posição no ranking de mais votados)"<<endl;
    for (list<Vereador*>::iterator vereador = listaTodosOsVereadores.begin(); vereador != listaTodosOsVereadores.end(); vereador++){
        Vereador *auxVereador = *vereador;
        i+=1;
        if (i>eleitos){      
            if (auxVereador->isEleito()){
                if (auxVereador->getColigacao()->getNome().compare(auxVereador->getPartido()->getNome())==0){
                    cout<<i<<" - "<<auxVereador->getNome()<<" ("<<auxVereador->getPartido()->getNome()<<", "<<auxVereador->getVotos()<<" votos)"<<endl;	
                }														
                else{
                    cout<<i<<" - "<<auxVereador->getNome()<<" ("<<auxVereador->getPartido()->getNome()<<", "<<auxVereador->getVotos()<<" votos) - Coligação: "<<auxVereador->getColigacao()->getNome()<<endl;
                }
            }
        }
    }
    cout<<endl;
}

void EleicaoDeVereadores::imprimeListaColigacoes(){
    int i=0;
    cout<<"Votação (nominal) das coligações e número de candidatos eleitos:"<<endl;
    for (list<Coligacao*>::iterator coligacao = listaTodasAsColigacoes.begin(); coligacao != listaTodasAsColigacoes.end(); coligacao++){
        Coligacao* auxCol = *coligacao;
        i+=1;
        if(auxCol->getVereadoresEleitos()<=1){
            cout<<i<<" - Coligação: "<<auxCol->getNome()<<", "<<auxCol->getVotosColigacao()<<" votos, "<<auxCol->getVereadoresEleitos()<<" canditado eleito"<<endl;		
        }																				
        else{
            cout<<i<<" - Coligação: "<<auxCol->getNome()<<", "<<auxCol->getVotosColigacao()<<" votos, "<<auxCol->getVereadoresEleitos()<<" canditados eleitos"<<endl;
        }
    }
    cout<<endl;
}

void EleicaoDeVereadores::imprimeListaPartidos(){
    cout<<"Votação (nominal) dos partidos e número de candidatos eleitos:"<<endl;
    int i=0;
    for (list<Partido*>::iterator partido = listaTodosOsPartidos.begin(); partido != listaTodosOsPartidos.end(); partido++){
        Partido* auxPar = *partido;
        i+=1;
        if (auxPar->getVereadoresEleitos()<=1){
            cout<<i<<" - "<<auxPar->getNome()<<", "<<auxPar->getVotosPartido()<<" votos, "<<auxPar->getVereadoresEleitos()<<" canditado eleito"<<endl;			
        }
        else{
            cout<<i<<" - "<<auxPar->getNome()<<", "<<auxPar->getVotosPartido()<<" votos, "<<auxPar->getVereadoresEleitos()<<" canditados eleitos"<<endl;
        }
    }
    cout<<endl<<"Total de votos nominais: "<<votosTotais<<endl;
}

EleicaoDeVereadores::EleicaoDeVereadores() {
}

EleicaoDeVereadores::EleicaoDeVereadores(const EleicaoDeVereadores& orig) {
}

EleicaoDeVereadores::~EleicaoDeVereadores() {
}

