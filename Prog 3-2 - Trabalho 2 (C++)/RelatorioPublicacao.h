//
// Created by Sandor ferreira da silva on 27/07/17.
//

#ifndef P3_T2_RELATORIOPUBLICACAO_H
#define P3_T2_RELATORIOPUBLICACAO_H


#include "Publicacao.h"

class RelatorioPublicacao {
    vector<Publicacao*> publicacoes;
    string pathname;
    string categoriasQualis[8] = {"A1", "A2", "B1", "B2", "B3", "B4", "B5", "C"};
    string const FILE_HEDER = "Ano;Sigla Veículo;Veículo;Qualis;Fator de Impacto;Título;Docentes";
    vector<Publicacao*> ordenarPorQualis(string qualis);
    int getMaiorAno(vector<Publicacao*> auxPubs);
    vector<Publicacao*> ordenarPorAno(int maiorAno, int ano, vector<Publicacao*> pubPorQualis);
    vector<string> getSortedStringArray(vector<string> array);
public:
    RelatorioPublicacao(string pathname, vector<Publicacao*> publicacoes);
    static vector<Publicacao*> ordenarPorSigla(vector<Publicacao*> auxPubs);
    vector<Publicacao*> ordenar();
    void write();


};


#endif //P3_T2_RELATORIOPUBLICACAO_H
