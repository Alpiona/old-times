package trabalho1;

import java.util.*;

/**
 * Essa classe tem como objetivo separar a parte de leitura do programa, para facilitar
 * o desenvolvimento e entendimento da lógica do programa.
 *
 */

public class Leitor {					
	
	private String nomeVereador, partido, coligacao, numero;
	private boolean eleito;
	private int votos, id;
	
	public String getNomeVereador() {
		return nomeVereador;
	}
	public void setNomeVereador(String nomeVereador) {
		this.nomeVereador = nomeVereador;
	}
	public String getPartido() {
		return partido;
	}
	public void setPartido(String partido) {
		this.partido = partido;
	}
	public String getColigacao() {
		return coligacao;
	}
	public void setColigacao(String coligacao) {
		this.coligacao = coligacao;
	}
	public boolean isEleito() {
		return eleito;
	}
	public void setEleito(boolean eleito) {
		this.eleito = eleito;
	}
	public int getVotos() {
		return votos;
	}
	public void setVotos(int votos) {
		this.votos = votos;
	}
	public int getId() {
		return id;
	}
	public void setId(int id) {
		this.id = id;
	}
	public String getNumero() {
		return numero;
	}
	public void setNumero(String numero) {
		this.numero = numero;
	}
	
	/**
	 * Esse método tem como objetivo receber uma linha do arquivo de entrada (um vereador), e dividir
	 * em variáveis.
	 * @param dados A linha lida
	 */
	
	public void pegaInformacaoDaLinha(String dados) {	
		
		String letra = dados.substring(0, 1);		//Pega o primeiro char da linha para indicar caso seja vereador eleito ou invalidado
		String[] dadosVereador = dados.split(";");  // [0]=ID; [1]=Número; [2]=Nome; [3]=Partido e Coligação; [4]=Votos; [5]=Porcentagem
		numero = dadosVereador[1];
		nomeVereador = dadosVereador[2];
		if (Objects.equals(letra, "*")){	
			id = Integer.valueOf(dadosVereador[0].substring(1)); //'If' para encontrar vereadores eleitos
			eleito = true;
		}	
		else if (Objects.equals(letra, "#")){
			id = Integer.valueOf(dadosVereador[0].substring(1)); //'If' para encontrar vereadores invalidados
			eleito = false;			
		}
		else {
			id = Integer.valueOf(dadosVereador[0]);		//Validados porém não eleitos
			eleito = false;
		}
		
		dadosVereador[4]= dadosVereador[4].replace(".", "");
		votos = Integer.valueOf(dadosVereador[4]);
		
		String[] dadosPartido = dadosVereador[3].split(" - "); //[0]=Partido; [1]=Coligação
		
		partido = dadosPartido[0];
		int qntPartidos = dadosPartido.length;
		if (qntPartidos>1){
			coligacao = dadosPartido[1];		//Caso o split não tenha dividido partido de coligação, então não tem coligação
		}
	}
}
