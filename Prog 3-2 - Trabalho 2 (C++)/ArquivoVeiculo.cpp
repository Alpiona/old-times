//#include <histedit.h>
#include "ArquivoVeiculo.h"
#include "ExceptionFile.h"
#include "util/Tokenizer.h"
#include "util/StringUtils.h"
#include "util/NumberUtils.h"
#include "util/NumPunctPTBR.h"

using namespace std;
using namespace cpp_util;

ArquivoVeiculo::ArquivoVeiculo(string pathname) {

    this->entrada.open(pathname);
    if(!(this->entrada.is_open())){
        throw ExceptionFile();
    }
    else{
        loadDataToMemory();
    }
}

void ArquivoVeiculo::loadDataToMemory() {
    string line;
    getline(this->entrada, line);
    while (getline(this->entrada, line)) {
        if (line != "") {

            cpp_util::Tokenizer tok(line,';');
            vector<string> dados = tok.remaining();
            for(unsigned i=0;i<dados.size();i++) {
                dados[i] = trim(dados[i]);
            }

            string sigla = dados[0];

            try {
                int isContained = 0;
                string wrongSigla;
                for(Veiculo* auxV : veiculos) {
                    if (auxV->getSigla().compare(sigla)==0) {
                        isContained = 1;
                    }
                    if(isContained==1){ wrongSigla = sigla;}
                }
                if(isContained==1) {
                    throw sigla;
                }

            } catch (string sigla) {
                ExceptionFile exceptionFile;
                exceptionFile.veiculoRepetido(sigla);
                exit(1);
            }
            string nome = dados[1];
            char tipo = dados[2].at(0);
            try {
                if(tipo != 'P' && tipo != 'C') {
                    throw make_pair(sigla, tipo);
                }
            } catch(pair<string, char> e) {
                ExceptionFile exceptionFile;
                exceptionFile.tipoVeiculoNaoDefinido(e.first, e.second);
                exit(1);
            }
            double impacto = parseDouble(dados[3],LOCALE_PT_BR);

            string ISSN = "";
            if(dados.size()>4) {
                ISSN = dados[4];
            }

            Veiculo* novoVeiculo = new Veiculo(sigla, nome, tipo, impacto, ISSN);
            this->veiculos.push_back(novoVeiculo);
        }
    }
}

vector<Veiculo*> ArquivoVeiculo::getVeiculos() {return this->veiculos;}
