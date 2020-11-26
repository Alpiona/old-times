package trabalho;
import java.io.Serializable;
import java.util.*;

public class Veiculo implements Serializable {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	private String sigla;
	private String nome;
	private char tipo;
	private double fatorDeImpacto;
	private String ISSN;
    private LinkedList<Qualis> listaQualis = new LinkedList<Qualis>();
	
	public Veiculo(String sigla, String nome, char tipo, double fatorDeImpacto, String ISSN) {
		this.sigla = sigla;
		this.nome = nome;
		this.tipo = tipo;
		this.fatorDeImpacto = fatorDeImpacto;
		this.ISSN = ISSN;
	}
	
	public String getSigla() {
		return sigla;
	}
	public String getNome() {
		return nome;
	}
	public char getTipo() {
		return tipo;
	}
	public double getFatorDeImpacto() {
		return fatorDeImpacto;
	}
	public String getISSN() {
		return ISSN;
	}
        
	public LinkedList<Qualis> getListaQualis (){
		return listaQualis;
	}
	
	public String toString() {
		return sigla + " " + nome;
	}
}
