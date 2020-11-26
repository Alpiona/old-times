#include "PublicacaoConferecia.h"

using namespace std;

PublicacaoConferecia::PublicacaoConferecia(int numero, int ano, int pgInicial, int pgFinal, string titulo,
                                           Veiculo* veiculo, string local, vector <Docente*> autores) :
        Publicacao(numero, ano, pgInicial, pgFinal, veiculo, autores, titulo){
    this->local = local;
}