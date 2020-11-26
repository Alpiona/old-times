#ifndef P3_T2_PUBLICACAOCONFERECIA_H
#define P3_T2_PUBLICACAOCONFERECIA_H

#include <string>
#include "Docente.h"
#include "Veiculo.h"
#include "Publicacao.h"

using namespace std;

class PublicacaoConferecia : public Publicacao{
private:
    string local;

public:
    PublicacaoConferecia(int numero, int ano, int pgInicial, int pgFinal, string titulo, Veiculo* veiculo, string local, vector<Docente*> autores);
};


#endif //P3_T2_PUBLICACAOCONFERECIA_H
