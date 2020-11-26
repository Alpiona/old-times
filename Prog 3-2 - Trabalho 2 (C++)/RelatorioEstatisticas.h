#ifndef P3_T2_RELATORIOESTATISTICAS_H
#define P3_T2_RELATORIOESTATISTICAS_H

#include "Publicacao.h"

class EstatisticaQualis{
private:
    std::string qualis;
    int nArtigos;
    double nArtigosPorDocente;
public:
    EstatisticaQualis(std::string qualis, int nArtigos, double nArtigosPorDocente);
    string getQualis();
    int getNArtigos();
    double returnArtigosPorDocente();
};

class RelatorioEstatisticas {
private:
    std::vector<Publicacao*> publicacoes;
    std::string pathname;
    std::string categoriasQualis[8] = {"A1", "A2", "B1", "B2", "B3", "B4", "B5", "C"};
    std::vector<EstatisticaQualis*> estatisticas;
public:
    RelatorioEstatisticas(string pathname, std::vector<Publicacao*> publicacoes);
    void getEstatisticaAllQualis();
    void getEstatisticasDeQualis(std::string qualis);
    void write();
};


#endif //P3_T2_RELATORIOESTATISTICAS_H
