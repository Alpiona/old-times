package trabalho1;

import java.util.LinkedList;

public class Coligacao {
	
	private String nome;
	private LinkedList<Partido> partidosDaColigacao = new LinkedList<Partido>();
	private int votosColigacao, vereadoresEleitos;

	public LinkedList<Partido> getPartidosDaColigacao() {
		return partidosDaColigacao;
	}

	public void setPartidoDaColigacao(LinkedList<Partido> partidosDaColigacao) {
		this.partidosDaColigacao = partidosDaColigacao;
	}
	
	public int getVereadoresEleitosCol(){
		return vereadoresEleitos;
	}
	
	public void setVereadoresEleitosCol (int vereadoresEleitosCol){
		this.vereadoresEleitos = vereadoresEleitosCol;
	}
	
	public int getVotosColigacao (){
		return votosColigacao;
	}
	
	public void setVotosColigacao(int votosColigacao){
		this.votosColigacao = votosColigacao;
	}

	public String getNome() {
		return nome;
	}

	public void setNome(String nome) {
		this.nome = nome;
	}
}
