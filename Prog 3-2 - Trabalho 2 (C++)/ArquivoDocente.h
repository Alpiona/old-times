#ifndef P3_T2_ARQUIVODOCENTE_H
#define P3_T2_ARQUIVODOCENTE_H

#include <string>
#include <vector>
#include <fstream>
#include "Docente.h"

class Docente;

class ArquivoDocente {
private:
    vector<Docente*> docentes;
    ifstream entrada;

public:
    ArquivoDocente();
    ArquivoDocente(std::string pathname);
    void loadDataToMemory();
    vector<Docente*> getDocentes();
    void addDocente (Docente docente);
};


#endif //P3_T2_ARQUIVODOCENTE_H
