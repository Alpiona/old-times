package trabalho;

import java.io.Serializable;
import java.util.Date;

public class RegraPontuacao implements Serializable {

    /**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	/*
	 * Classe RegraPontuacao
	 * receve do arquivo de entrada de regras
	 * gera na memória local a classe RegraPontuacao
     */
    private Date dataInicio, dataFinal;
    private String[] categoriasQualis = {"A1", "A2", "B1", "B2", "B3", "B4", "B5", "C"};
    private int[] pontuacaoQualis;
    private double multiplicador;
    private int qtdAnos, pontuacaoMinima;

    public RegraPontuacao(Date dataInicio, Date dataFinal, int[] pontuacaoQualis, double multiplicador, int qtdAnos,
            int pontuacaoMinima) {
        this.dataInicio = dataInicio;
        this.dataFinal = dataFinal;
        this.pontuacaoQualis = pontuacaoQualis;
        this.multiplicador = multiplicador;
        this.qtdAnos = qtdAnos;
        this.pontuacaoMinima = pontuacaoMinima;
    }

    public RegraPontuacao() {
    }

    public String[] getCategoriasQualis() {
        return categoriasQualis;
    }

    public int[] getPontuacaoQualis() {
        return pontuacaoQualis;
    }

    public Date getDataInicio() {
        return dataInicio;
    }

    public Date getDataFinal() {
        return dataFinal;
    }

    public double getMultiplicador() {
        return multiplicador;
    }

    public int getQtdAnos() {
        return qtdAnos;
    }

    public int getPontuacaoMinima() {
        return pontuacaoMinima;
    }

    public int valorQualis(String qualis) {
        int i = 0;
        for (String auxqualis : categoriasQualis) {
            if (auxqualis.equals(qualis)) {
                return pontuacaoQualis[i];
            }
            i++;
        }
        return 0;
    }

    public String toString() {
        return String.valueOf(multiplicador);
    }

}
