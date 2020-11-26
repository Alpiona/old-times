//#include <histedit.h>
#include "ArquivoQualificacoes.h"
#include "ExceptionFile.h"
#include "util/StringUtils.h"
#include "util/Tokenizer.h"

using namespace std;
using namespace cpp_util;

ArquivoQualificacoes::ArquivoQualificacoes(string pathname, vector<Veiculo*> veiculos) {
    this->veiculos = veiculos;
    this->entrada.open(pathname);
    if (!(this->entrada.is_open())){
        throw ExceptionFile();
    } else {
        loadDataToLocalMemory();
    }
}

void ArquivoQualificacoes::loadDataToLocalMemory() {
    string line;
    getline(this->entrada,line);
    while (getline(this->entrada, line)) {
        if (line != "") {

            cpp_util::Tokenizer tok(line, ';');
            vector<string> tokens = tok.remaining();
            for(unsigned i=0;i<tokens.size();i++) {
                tokens[i] = trim(tokens[i]);
                //cout << tokens[i] << endl;
            }

            int ano;
            try {
                ano = stoi(tokens[0]);
            } catch (invalid_argument &e) {
                cout << e.what() << endl;
            }

            string siglaVeiculo = tokens[1];
            string qualis = tokens[2];

            try {
                int isContained = 0;
                for(Veiculo* auxV : veiculos) {
                    if(auxV->getSigla().compare(siglaVeiculo)==0) {
                        isContained = 1;
                    }
                }
                if(isContained == 0) {
                    throw make_pair(ano, siglaVeiculo);
                }
            } catch (pair<int, string> e) {
                ExceptionFile exceptionFile;
                exceptionFile.siglaVeiculoNaoDefinidaQualificacao(e.first,e.second);
                exit(1);
            }

            //int pontuacaoDaQualis = this->regra->valorQualis(qualis);
            Qualis *novoQualis = new Qualis(ano, qualis, siglaVeiculo);
            try {
                if (!novoQualis->isValidQualis()) {
                    throw siglaVeiculo;
                }
            } catch (string siglaVeiculo) {
                ExceptionFile exceptionFile;
                exceptionFile.qualisDesconhecido(siglaVeiculo,ano,qualis);
                exit(1);
            }
            qualificacoes.push_back(novoQualis);
            for(unsigned i=0;i<veiculos.size();i++) {
                if(veiculos[i]->getSigla().compare(siglaVeiculo)==0) {
                    veiculos[i]->addQualis(novoQualis);
                }
            }
        }
    }
}

//vector<Veiculo*> ArquivoQualificacoes::getNovosVeiculos() {
//    return this->novosVeiculos;
//}

Veiculo* ArquivoQualificacoes::encontraVeiculo(string sigla) {
    Veiculo* veiculo = NULL;
    for(Veiculo* v: this->veiculos) {
        if(v->getSigla().compare(sigla) == 0) {
            veiculo = v;
        }
    }
    return veiculo;
}

vector<Qualis*> ArquivoQualificacoes::getListaQualis() {return this->qualificacoes;}

void ArquivoQualificacoes::setRegra(RegraPontuacao* regraPontuacao) {
    this->regra = regraPontuacao;
    this->colocarPontuacaoQualis();
}

void ArquivoQualificacoes::colocarPontuacaoQualis() {
    for(unsigned i=0;i<this->qualificacoes.size();i++) {
        this->qualificacoes[i]->setPontuacao(this->regra->valorQualis(qualificacoes[i]->getQualis()));
    }
}