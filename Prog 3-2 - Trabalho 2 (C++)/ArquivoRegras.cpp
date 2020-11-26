#include "ArquivoRegras.h"
#include "ExceptionFile.h"
#include "util/DateUtils.h"
#include "util/NumberUtils.h"
#include "util/Tokenizer.h"
#include "util/StringUtils.h"
#include <locale>

using namespace std;
using namespace cpp_util;

ArquivoRegras::ArquivoRegras(string pathname) {
    this->entrada.open(pathname);
    if (!(this->entrada.is_open())){
        throw ExceptionFile();
    }
    else{loadDataToMemory();}
}

RegraPontuacao* ArquivoRegras::getRegra(string ano) {
    for(unsigned i=0;i<this->regras.size();i++) {
        if(regras[i]->getAno().compare(ano) == 0) {
            return regras[i];
        }
    }
}

void ArquivoRegras::loadDataToMemory(){

    string line;
    getline(this->entrada,line);

    while(getline(this->entrada,line)) {
        vector<string> todosQualis = {"A1", "A2", "B1", "B2", "B3", "B4", "B5", "C"};
        Tokenizer splitter(line,';');
        vector<string> dados = splitter.remaining();
        for(unsigned i=0;i<dados.size();i++) {
            dados[i] = trim(dados[i]);
        }
        time_t dataInicioVigencia, dataFimVigencia;
        if(validDate(dados[0],DATE_FORMAT_PT_BR_SHORT) && validDate(dados[1],DATE_FORMAT_PT_BR_SHORT)) {
            dataInicioVigencia = parseDate(dados[0],DATE_FORMAT_PT_BR_SHORT);
            dataFimVigencia = parseDate(dados[0],DATE_FORMAT_PT_BR_SHORT);
        }

        Tokenizer qualisToken(dados[2],',');
        vector<string> categoriasQualis = qualisToken.remaining();
        for(unsigned i=0;i<categoriasQualis.size();i++) {
            categoriasQualis[i] = trim(categoriasQualis[i]);
        }

        try {
            int isValid = 0;
            string wrongQualis;
            for(string auxQualis : categoriasQualis) {
                for(string atQualis : this->todosQualis) {
                    if(auxQualis.compare(atQualis)==0) {
                        isValid = 1;
                    }
                }
                if(isValid == 0) { wrongQualis = auxQualis; break;}
            }
            if(isValid == 0) {
                throw make_pair(dados[0],wrongQualis);
            }
        } catch(pair<string, string> e) {
            ExceptionFile exceptionFile;
            exceptionFile.qualisDesconhecidoParaRegra(e.first, e.second);
            exit(1);
        }

        Tokenizer pontuacaoToken(dados[3],',');
        vector<string> auxString = pontuacaoToken.remaining();
        for(unsigned i=0;i<auxString.size();i++) {
            auxString[i] = trim(auxString[i]);
        }

        vector<int> pontuacaoQualis;

        int iteratorPontuacao = 0;
        for(unsigned i=0;i<todosQualis.size();i++) {
            if (todosQualis[i].compare(categoriasQualis[iteratorPontuacao + 1]) == 0) { iteratorPontuacao++; }
            int pontuacao;
            try {
                pontuacao = stoi(auxString[iteratorPontuacao]);
            } catch (invalid_argument argument) {
                cout << argument.what() << endl;
            }
            pontuacaoQualis.push_back(pontuacao);
        }

        double multiplicador = parseDouble(dados[4],LOCALE_PT_BR);
        int anos;
        try {
            anos = stoi(dados[5]);
        } catch (invalid_argument argument) {
            cout << argument.what() << endl;
        }
        int pontuacaoMinima;

        try {
            pontuacaoMinima = stoi(dados[6]);
        } catch (invalid_argument argument) {
            cout << argument.what() << endl;
        }

        RegraPontuacao* regra = new RegraPontuacao(pontuacaoQualis, multiplicador, anos, pontuacaoMinima, dataInicioVigencia, dataFimVigencia);
        regras.push_back(regra);
    }
//    string aux;
//    size_t pos = 0;
//    string separador = ";";
//
//    pos = line.find(separador);
//    aux = line.substr(0, pos);
//    time_t dInicio;
//    if(validDate(aux,DATE_FORMAT_PT_BR_SHORT)) {
//        dInicio = parseDate(aux, DATE_FORMAT_PT_BR_SHORT);
//    }
//    line.erase(0, pos + 1);
//
//    pos = line.find(separador);
//    aux = line.substr(0, pos);
//    time_t dFinal;
//    if(validDate(aux,DATE_FORMAT_PT_BR_SHORT)) {
//        dFinal = parseDate(aux, DATE_FORMAT_PT_BR_SHORT);
//    }
//    line.erase(0, pos + 1);
//
//    pos = line.find(separador);
//    aux = line.substr(0, pos);
//    string qualis = aux;
//    line.erase(0, pos + 1);
//    string unicoQualis;
//
//
//    pos = line.find(separador);
//    aux = line.substr(0, pos);
//    string pontos = aux;
//    line.erase(0, pos + 1);
//
//    array<string,8> categoriasQualis = {"A1", "A2", "B1", "B2", "B3", "B4", "B5", "C"};
//    array<int,8> pontuacaoQualis = {0,0,0,0,0,0,0,0};
//    int unicoPonto;
//    int i =0;
//    while (qualis.find(",") != string::npos) {
//        i=0;
//        pos = qualis.find(",");
//        aux = qualis.substr(0, pos);
//        unicoQualis = aux;
//        qualis.erase(0, pos + 1);
//
//        pos = pontos.find(",");
//        aux = pontos.substr(0, pos);
//        unicoPonto = atoi(aux.c_str());
//        pontos.erase(0, pos + 1);
//
//        while (categoriasQualis[i].compare(unicoQualis) != 0) {
//            if (pontuacaoQualis[i] == 0 && i != 0){
//                pontuacaoQualis[i] = pontuacaoQualis[i-1];
//            }
//            i++;
//        }
//        pontuacaoQualis[i] = unicoPonto;
//    }
//
//    while (categoriasQualis[i].compare(qualis) != 0) {
//        if (pontuacaoQualis[i] == 0 && i != 0){
//            pontuacaoQualis[i] = pontuacaoQualis[i-1];
//        }
//        i++;
//    }
//    while (i<8){
//        pontuacaoQualis[i] = atoi(pontos.c_str());
//        i++;
//    }
//
//    pos = line.find(separador);
//    aux = line.substr(0, pos);
//    double multiplicador  = atof(aux.c_str()); //pega como float mas n considera a virgula
//    line.erase(0, pos + 1);
//
//    pos = line.find(separador);
//    aux = line.substr(0, pos);
//    int anos = atoi(aux.c_str());
//    line.erase(0, pos + 1);
//
//    pos = line.find(separador);
//    aux = line.substr(0, pos);
//    int pontosMinimos = atoi(aux.c_str());
//
//    RegraPontuacao* regraPontuacao = new RegraPontuacao(pontuacaoQualis, multiplicador, anos, pontosMinimos, dInicio, dFinal);
//
//    this->regras.push_back(regraPontuacao);
}
