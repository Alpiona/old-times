#include "Publicacao.h"

using namespace std;

Publicacao::Publicacao(int numero, int ano, int pgInicial, int pgFinal, Veiculo* veiculo,
                       vector<Docente*> autores, string titulo) {
    this->numero = numero;
    this->ano = ano;
    this->pgInicial = pgInicial;
    this->pgFinal = pgFinal;
    this->veiculo = veiculo;
    this->autores = autores;
    this->titulo = titulo;
}

string Publicacao::getNome() {return this->titulo;}
int Publicacao::getAno() {return this->ano;}
string Publicacao::getQualis() {return this->qualis;}
void Publicacao::setQualis(string qualis) {this->qualis = qualis; }
vector<Docente*> Publicacao::getAutores() {return this->autores;}

string Publicacao::getFormatListaAutores() {
    int i = 0;
    string nomes;
    for(Docente* d: this->autores) {
        if(i == this->autores.size() - 1) {
            nomes = d->getNome();
        } else {
            nomes = d->getNome() + ",";
        }
        i++;
    }
    return nomes;
}

bool Publicacao::operator==(Publicacao* const& p2) {
    //return p1.getAno() == p2.getAno();
    return ((this->getNome().compare(p2->getNome())));
}

Veiculo* Publicacao::getVeiculo() {return this->veiculo;}