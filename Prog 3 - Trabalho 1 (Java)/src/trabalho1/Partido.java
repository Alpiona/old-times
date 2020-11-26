package trabalho1;

import java.util.LinkedList;

public class Partido {

	private Coligacao coligacao;
	private String nome;
	private LinkedList<Vereador> vereadoresDoPartido = new LinkedList<Vereador>();
	private int votosPartido, vereadoresEleitos;
	
	public LinkedList<Vereador> getVereadoresDoPartido() {
		return vereadoresDoPartido;
	}
	public void setVereadoresDoPartido(LinkedList<Vereador> vereadoresDoPartido) {
		this.vereadoresDoPartido = vereadoresDoPartido;
	}
	public int getVotosTotal() {
		return votosPartido;
	}
	public void setVotosTotal(int votosPartido) {
		this.votosPartido = votosPartido;
	}
	public int getVereadoresEleitos() {
		return vereadoresEleitos;
	}
	public void setVereadoresEleitos(int vereadoresEleitosPar) {
		this.vereadoresEleitos = vereadoresEleitosPar;
	}
	public String getNome() {
		return nome;
	}
	public void setNome(String nome) {
		this.nome = nome;
	}
	public Coligacao getColigacao() {
		return coligacao;
	}
	public void setColigacao(Coligacao coligacao) {
		this.coligacao = coligacao;
	}

}