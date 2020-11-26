package trabalho.Relatorio;

import trabalho.*;
import java.util.Collections;
import java.util.LinkedList;
import java.util.Locale;
import java.util.Vector;
import java.io.FileWriter;
import java.io.IOException;

public class RelatorioPublicacoes {

    /*
     * Criação do Relatório de Publicações
     * Classe RelatorioPublicacoes
     */
    private LinkedList<Publicacao> publicacoes;
    private String pathname;
    private String[] categoriasQualis = {"A1", "A2", "B1", "B2", "B3", "B4", "B5", "C"};

    // File Writer - constantes estáticas e finais
    private static final String COMMA_DELIMITER = ";";
    private static final String NEW_LINE_SEPARATOR = "\n";
    private static final String FILE_HEADER = "Ano;Sigla Veículo;Veículo;Qualis;Fator de Impacto;Título;Docentes";

    // Construtor
    public RelatorioPublicacoes(String pathname, LinkedList<Publicacao> publicacoes) {
        this.publicacoes = publicacoes;
        this.pathname = pathname;
    }

    //Ordenando por Qualis...
    private LinkedList<Publicacao> ordenarPorQualis(String qualis) {
        LinkedList<Publicacao> auxPub = new LinkedList<Publicacao>();

        for (Publicacao auxPublicacao : publicacoes) {
            if (auxPublicacao.getQualis().equals(qualis)) {
                auxPub.add(auxPublicacao);
            }
        }
        return auxPub;
    }

    private int getMaiorAno(LinkedList<Publicacao> auxPubs) {
        int maiorAno = 0;
        for (Publicacao auxPub : auxPubs) {
            maiorAno = auxPub.getAno();
            break;
        }
        for (Publicacao auxPublicacao : auxPubs) {
            if (auxPublicacao.getAno() >= maiorAno) {
                maiorAno = auxPublicacao.getAno();
            }
        }
        return maiorAno;
    }

    private LinkedList<Publicacao> ordenarPorAno(int maiorAno, int ano, LinkedList<Publicacao> pubPorQualis) {
        //Ordenando por ano

        LinkedList<Publicacao> auxSiglas = new LinkedList<Publicacao>();
        for (Publicacao auxPub : pubPorQualis) {
            if (auxPub.getAno() == ano) {
                auxSiglas.add(auxPub);
            }
        }
        /*
			 * Dentro de Ordem por ano, já ordenar por sigla
			 * Ordenando por sigla, ordenando por título internamente
         */
        auxSiglas = this.ordenarPorSigla(auxSiglas);
        return auxSiglas;
    }

    private LinkedList<Publicacao> ordenarPorSigla(LinkedList<Publicacao> auxPubs) {

        /*
		 * Ordenando por sigla
         */
        LinkedList<Publicacao> returnedSiglaAndTitulo = new LinkedList<Publicacao>();
        Vector<String> auxSiglasString = new Vector<String>();
        for (Publicacao auxPub : auxPubs) {
            auxSiglasString.add(auxPub.getVeiculo().getSigla());
        }
        auxSiglasString = this.getSortedStringArray(auxSiglasString);

        for (String sigla : auxSiglasString) {
            LinkedList<Publicacao> auxSiglaHS = new LinkedList<Publicacao>();
            for (Publicacao auxPub : auxPubs) {
                if (auxPub.getVeiculo().getSigla().equals(sigla)) {
                    auxSiglaHS.add(auxPub);
                }
            }

            LinkedList<Publicacao> vetorTituloOrdenado = new LinkedList<Publicacao>();
            Vector<String> titulos = new Vector<String>();
            for (Publicacao auxPublicacaoTitulo : auxSiglaHS) {
                titulos.add(auxPublicacaoTitulo.getTitulo());
            }
            titulos = this.getSortedStringArray(titulos);
            for (String titulo : titulos) {
                for (Publicacao auxPub : auxSiglaHS) {
                    if (titulo.equals(auxPub.getTitulo())) {
                        vetorTituloOrdenado.add(auxPub);
                    }
                }
            }
            for (Publicacao okok : vetorTituloOrdenado) {
                returnedSiglaAndTitulo.add(okok);
            }
        }
        return returnedSiglaAndTitulo;
    }

    public LinkedList<Publicacao> ordenar() {
        LinkedList<Publicacao> hashOrdenada = new LinkedList<Publicacao>();

        for (Publicacao auxPublicacao : publicacoes) {
            LinkedList<Qualis> qualisPossiveis = auxPublicacao.getVeiculo().getListaQualis();

            for (Qualis auxQualis : qualisPossiveis) {
                auxPublicacao.setQualis(auxQualis.getQualis());
            }
        }

        for (String categoriaQualis : categoriasQualis) {
            // ordenando por qualis
            LinkedList<Publicacao> auxPubs = new LinkedList<Publicacao>();
            LinkedList<Publicacao> pubPorQualis = this.ordenarPorQualis(categoriaQualis);
            int maiorAno = this.getMaiorAno(pubPorQualis);
            for (int ano = maiorAno; ano > 2007; ano--) {
                LinkedList<Publicacao> ordenadoPorAno = this.ordenarPorAno(maiorAno, ano, pubPorQualis);
                for (Publicacao okok : ordenadoPorAno) {
                    auxPubs.add(okok);
                }
            }

            for (Publicacao okok : auxPubs) {
                hashOrdenada.add(okok);
            }
        }
        return hashOrdenada;
    }

    public void write() {

        /*
	     * Escrita de Arquivo CSV com HEADER, LINE E DELIMITER
	     * Relatório número 2
         */
        LinkedList<Publicacao> hashOrdered = this.ordenar();

        FileWriter fileWriter = null;
        
        Locale localeBrasil = new Locale("pt", "BR");

        try {
            fileWriter = new FileWriter(pathname);
            fileWriter.append(FILE_HEADER.toString());
            fileWriter.append(NEW_LINE_SEPARATOR.toString());

            for (Publicacao p : hashOrdered) {
                fileWriter.append(String.valueOf(p.getAno()));
                fileWriter.append(COMMA_DELIMITER.toString());
                fileWriter.append(p.getVeiculo().getSigla());
                fileWriter.append(COMMA_DELIMITER.toString());
                fileWriter.append(p.getVeiculo().getNome());
                fileWriter.append(COMMA_DELIMITER.toString());
                fileWriter.append(p.getQualis());
                fileWriter.append(COMMA_DELIMITER.toString());
                fileWriter.append(String.format(localeBrasil, "%.3f", p.getVeiculo().getFatorDeImpacto()));
                fileWriter.append(COMMA_DELIMITER.toString());
                fileWriter.append(p.getTitulo());
                fileWriter.append(COMMA_DELIMITER.toString());
                int lenghAutores = p.getAutores().size();
                int i = 0;
                for (Docente d : p.getAutores()) {
                    if (i == lenghAutores - 1) {
                        fileWriter.append(d.getNome());
                    } else {
                        fileWriter.append(d.getNome() + ",");
                    }
                    i++;
                }
                fileWriter.append(NEW_LINE_SEPARATOR.toString());
            }

        } catch (Exception e) {
            System.out.println("Erro de I/O");
            //(1);
        } finally {
            try {
                fileWriter.flush();
                fileWriter.close();
            } catch (IOException e) {
                System.out.println("Erro de I/O");
                //(1);
            }

        }

    }

    private Vector<String> getSortedStringArray(Vector<String> array) {
        Collections.sort(array);
        Vector<String> newArray = new Vector<String>();
        for (String auxArray : array) {
            if (!newArray.contains(auxArray)) {
                newArray.add(auxArray);
            }
        }
        return newArray;
    }

}
