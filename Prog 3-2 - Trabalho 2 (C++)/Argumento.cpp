//
// Created by Sandor ferreira da silva on 31/07/17.
//

#include "Argumento.h"
Argumento::Argumento(int argc, char* args[]) {
    //-d docentes.csv -v veiculos.csv -p publicacoes.csv -q qualis.csv -r regras.csv -a 2017
    for(unsigned i=0;i<argc/2;i++) {
        this->args[args[(i*2)+1]] = args[(i*2)+2];
    }
}

string Argumento::get(string value) {
    return this->args.find(value)->second;
}

