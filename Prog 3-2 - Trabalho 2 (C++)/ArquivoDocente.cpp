#include "ArquivoDocente.h"
#include "ExceptionFile.h"
#include "util/DateUtils.h"
#include "util/StringUtils.h"
#include "util/Tokenizer.h"
#include <iostream>

using namespace std;
using namespace cpp_util;

ArquivoDocente::ArquivoDocente() {}

ArquivoDocente::ArquivoDocente(string pathname) {

    this->entrada.open(pathname);
    if (!(this->entrada.is_open())){
        throw new ExceptionFile();
    } else {
        loadDataToMemory();
    }

}

void ArquivoDocente::loadDataToMemory(){
    string line;
    getline(this->entrada, line);
    while (getline(this->entrada,line)) {
        if (line != "") {
            bool cord = false;
            Tokenizer tokenizer(line,';');
            vector<string> dados = tokenizer.remaining();
            for(unsigned i = 0;i<dados.size();i++) {
                dados[i] = trim(dados[i]);
            }

            string codigo = dados[0];
            try {
                for (Docente *auxDoc : this->docentes) {
                    if (codigo.compare(auxDoc->getCodigo()) == 0) {
                        throw (codigo);
                    }
                }
            } catch (string codigo){
                ExceptionFile e;
                e.docenteRepetido(codigo);
                ////(1);
            }
            string nome = dados[1];
            if(dados.size() > 4 && dados[4].compare("X") == 0) {
                cord = true;
            }

            // CRIAR EXCEÇÃO
            time_t dNascimento, dIngresso;
            if(validDate(dados[2],DATE_FORMAT_PT_BR_SHORT) && validDate(dados[3],DATE_FORMAT_PT_BR_SHORT)) {
                dNascimento = parseDate(dados[2],DATE_FORMAT_PT_BR_SHORT);
                dIngresso = parseDate(dados[3],DATE_FORMAT_PT_BR_SHORT);
            }

            Docente *novoDocente = new Docente(codigo, nome, cord, dNascimento, dIngresso);
            this->docentes.push_back(novoDocente);
        }
    }
}

vector<Docente*> ArquivoDocente::getDocentes(){
    return this->docentes;
}