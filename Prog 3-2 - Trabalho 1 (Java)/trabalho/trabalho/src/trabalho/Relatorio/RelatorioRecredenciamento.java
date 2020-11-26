package trabalho.Relatorio;

import java.io.*;
import java.text.*;
import trabalho.*;
import java.util.*;
import java.util.concurrent.TimeUnit;

public class RelatorioRecredenciamento {

    /*
     * Criação do Relatório Recredenciamento
     * Classe RelatorioRecredenciamento
     */
    private LinkedList<Docente> docentes;
    private String pathname;
    private RegraPontuacao regra;
    private Date hoje = new Date();

    private static final String FILE_HEADER = "Docente;Pontuação;Recredenciado?";

    public RelatorioRecredenciamento(String pathname, LinkedList<Docente> docentes, RegraPontuacao regra) {
        this.docentes = docentes;
        this.pathname = pathname;
        this.regra = regra;
    }

    private void ordenaDocentes() {
        this.docentes.sort(new Comparator<Docente>() {
            public int compare(Docente o1, Docente o2) {
                return Collator.getInstance().compare(o1.getNome(), o2.getNome());
            }
        });
    }

    public long DiferencaDatas(Date data1, Date data2) {
        long diff = data1.getTime() - data2.getTime();
        return TimeUnit.DAYS.convert(diff, TimeUnit.MILLISECONDS);
    }

    public void write() {
        /*
    	 * Escritura em arquivo CSV com parâmetros HEADER
         */
    	
    	Locale localeBrasil = new Locale("pt","BR");
    	
        ordenaDocentes();
        FileWriter fileWriter = null;
        try {
            fileWriter = new FileWriter(pathname);
            fileWriter.append(FILE_HEADER.toString() + "\n");
            double pontos;
            String especificacao;
            for (Docente auxDocente : docentes) {
                pontos = 0;
                especificacao = "Não";
                for (Publicacao auxPublicacao : auxDocente.getPublicacoes()) {

                    // Verificando tipo de Publicação e Veículo
                    if (auxPublicacao.getVeiculo().getTipo() == 'P') {
                        pontos += regra.valorQualis(auxPublicacao.getQualis()) * regra.getMultiplicador();
                    } else {
                        pontos += regra.valorQualis(auxPublicacao.getQualis());
                    }

                }
                if (pontos >= regra.getPontuacaoMinima()) {
                    especificacao = "Sim";
                }

                if (DiferencaDatas(hoje, auxDocente.getDataNascimento()) >= (365.25 * 60)) {
                    especificacao = "PPS";
                }

                if (DiferencaDatas(hoje, auxDocente.getDataIngresso()) <= (365.25 * 3)) {
                    especificacao = "PPJ";
                }

                if (auxDocente.isCoordenador()) {
                    especificacao = "Coordenador";
                }

                fileWriter.append(auxDocente.getNome() + ";" + String.format(localeBrasil, "%.1f", pontos) + ";" + especificacao + "\n");
            }

        } catch (Exception e) {
            System.out.println("Erro de I/O");

        } finally {
            try {
                fileWriter.flush();
                fileWriter.close();
            } catch (IOException e) {
                System.out.println("Erro de I/O");
            }

        }
    }
}
