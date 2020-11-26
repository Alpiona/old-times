#ifndef P3_T2_ARQUIVOPUBLICACOES_H
#define P3_T2_ARQUIVOPUBLICACOES_H

#include <string>
#include <fstream>
#include "Docente.h"
#include "Veiculo.h"
#include "Publicacao.h"
#include "PublicacaoConferecia.h"
#include "PublicacaoPeriodico.h"

class Docente;
class ArquivoPublicacoes {
private:
    std::ifstream entrada;
    std::vector<Docente*> docentes;
    std::vector<Veiculo*> veiculos;
    std::vector<Publicacao*> publicacoes;
    Veiculo containsVeiculoDeSigla(std::string pTitulo, std::string sigla);
    //std::vector<Docente*> loadListaAutoires(string[] autores, std::string pTitulo);
    Docente isCodigoDocenteValid (std::string codigo);

public:
    ArquivoPublicacoes(std::string pathname, std::vector<Docente*> docentes, std::vector<Veiculo*> veiculos);
    void loadDataToLocalMemory();
    std::vector<Publicacao*> getPublicacoes();
    void adicionarPubAoAutor (Publicacao* p, std::vector<Docente*> autores);
    vector<Docente*> loadListaAutores (std::vector<string> autores);
    Docente* encontraDocente(string codigo);
    Veiculo* encontraVeiculo(string veiculo);
};


#endif //P3_T2_ARQUIVOPUBLICACOES_H
