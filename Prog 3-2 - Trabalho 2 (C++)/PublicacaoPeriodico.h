#ifndef P3_T2_PUBLICACAOPERIODICO_H
#define P3_T2_PUBLICACAOPERIODICO_H

#include <string>
#include "Docente.h"
#include "Veiculo.h"
#include "Publicacao.h"

class PublicacaoPeriodico  : public Publicacao{
private:
    int volume;

public:
    PublicacaoPeriodico(int numero, int ano, int volume, int pgInicial, int pgFinal, string titulo,
                        Veiculo* veiculo, vector<Docente*> autores);
};


#endif //P3_T2_PUBLICACAOPERIODICO_H
