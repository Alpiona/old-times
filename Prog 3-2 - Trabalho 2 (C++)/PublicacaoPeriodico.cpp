#include "PublicacaoPeriodico.h"

PublicacaoPeriodico::PublicacaoPeriodico(int numero, int ano, int volume, int pgInicial, int pgFinal, string titulo,
                                         Veiculo* veiculo, vector <Docente*> autores) :
        Publicacao(numero, ano, pgInicial, pgFinal, veiculo, autores, titulo) {
    this->volume = volume;
}