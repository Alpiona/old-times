package trabalho1;

import java.util.*;

/**
 * Essa classe foi feita para organizar e imprimir os dados da maneira necessária.
 */

public class Saida {					
	
	private LinkedList<Vereador> listaVereadoresPorVotos = new LinkedList<Vereador>();
	private LinkedList<Partido> listaPartidosPorVotos = new LinkedList<Partido>();
	private LinkedList<Coligacao> listaColigacoesPorVotos = new LinkedList<Coligacao>();
	private int eleitos;
	
	public LinkedList<Vereador> getListaVereadoresPorVotos(){		
		return listaVereadoresPorVotos;
	}
	
	public LinkedList<Partido> getListaPartidosPorVotos(){
		return listaPartidosPorVotos;
	}
	
	public LinkedList<Coligacao> getListaColigacoesPorVotos(){
		return listaColigacoesPorVotos;
	}
	/**
	 * Esse metódo irá utilizar uma lista vazia de vereadores existente nessa classe para criar uma lista com
	 * os mesmos vereadores da lista já criada, porém organizada em ordem do verador com mais votos, para o com menos
	 * @param eleicao Lista com todos os vereadores encontrados pelo programa
	 */
	public void ordenaVereadoresPorVotos (EleicaoDeVereadores eleicao){
		Vereador vereadorMaisVotado = new Vereador();
		boolean listaIncompleta = true;
		while (listaIncompleta){												//Irá sempre adicionar a lista o vereador com mais votos
			listaIncompleta = false;											//e que ainda não tenha sido adicionado
			for (Vereador vereador : eleicao.getTodosOsVereadores()){			
				if (vereadorMaisVotado.getVotos()<=vereador.getVotos()&&(!(listaVereadoresPorVotos.contains(vereador)))){
					vereadorMaisVotado = vereador;								
					listaIncompleta=true;										//Foi usado 'menor ou igual' para não ter problema comparando
				}																//a mesma quantidade de votos, como o caso de 0 votos
			}
			if (listaIncompleta==true){
				listaVereadoresPorVotos.add(vereadorMaisVotado);
				vereadorMaisVotado = new Vereador();
			}														
		}
	}
	
	/**
	 * Esse método faz a contagem de vereadores eleitos usando a lista de partidos, para encontrar a quantidade de vagas.
	 * @param eleicao Lista com todos os partidos encontrados pelo programa
	 */
	
	public void numeroVagas(EleicaoDeVereadores eleicao){
		int vagas=0;
		for (Partido partido : eleicao.getPartidos()){
			vagas+=partido.getVereadoresEleitos();						
		}																
		System.out.println("Número de vagas: "+vagas+"\n");
		eleitos=vagas;
	}
	
	/**
	 * É utilizado a lista de vereadores ordenada por votos para imprimir os vereadores eleitos.
	 */
	
	public void vereadoresEleitos(){
		System.out.println("Vereadores eleitos:");
		for (Vereador vereador : getListaVereadoresPorVotos()){
			if (vereador.isEleito()){
				if (vereador.getColigacao()==null){
					System.out.println(vereador.getId()+" - "
							+vereador.getNome()+" ("
							+vereador.getPartido().getNome()+", "
							+vereador.getVotos()+" votos)");			//Apenas passa a lista de vereadores e imprime os eleitos
				}
				else{
					System.out.println(vereador.getId()+" - "
							+vereador.getNome()+" ("						//Toda a função de imprimir a lista de vereadores, irá verificar se 
							+vereador.getPartido().getNome()+", "			//possui coligação por motivo de organização
							+vereador.getVotos()+" votos) - Coligação: "
							+vereador.getColigacao().getNome());
				}
			}
		}
		System.out.println();
	}
	
	/**
	 * Utiliza a lista de vereadores ordenado por votos para imprimir os vereadores mais votados usando a quantidade de vagas como referência.
	 */
	
	public void vereadoresMaisVotados(){
		int i=0;
		System.out.println("Candidatos mais votados (em ordem decrescente de votação e respeitando número de vagas):");
		for (Vereador vereador : getListaVereadoresPorVotos()){
			if (i<eleitos){
				i+=1;
				if (vereador.getColigacao()==null){
					System.out.println(i+" - "
							+vereador.getNome()+" ("
							+vereador.getPartido().getNome()+", "
							+vereador.getVotos()+" votos)");	
				}														
				else{
					System.out.println(i+" - "
							+vereador.getNome()+" ("
							+vereador.getPartido().getNome()+", "
							+vereador.getVotos()+" votos) - Coligação: "
							+vereador.getColigacao().getNome());
				}
			}
		}
		System.out.println();
	}
	
	/**
	 * Utiliza a lista de vereadores ordenado por votos para imprimir os vereadores que teriam sido eleitos se a votação fosse
	 * majoritária.
	 */
	
	public void seriamEleitosSeMajoritario(){
		int i=0;
		System.out.println("Teriam sido eleitos se a votação fosse majoritária, e não foram eleitos:");
		System.out.println("(com sua posição no ranking de mais votados)");
		for (Vereador vereador : getListaVereadoresPorVotos()){
			if (i<eleitos){
				i+=1;
				if (!(vereador.isEleito())){
					if (vereador.getColigacao()==null){
						System.out.println(i+" - "
								+vereador.getNome()+" ("
								+vereador.getPartido().getNome()+", "
								+vereador.getVotos()+" votos)");			//O mesmo que a função anterior, porém só imprime se 
					}														//o vereador não tiver sido eleito
					else{
						System.out.println(i+" - "
								+vereador.getNome()+" ("
								+vereador.getPartido().getNome()+", "
								+vereador.getVotos()+" votos) - Coligação: "
								+vereador.getColigacao().getNome());
					}
				}
			}
		}
		System.out.println();
	}
	/**
	 * Utiliza a lista de vereadores ordenado por votos para imprimir os vereadores que foram eleitos graças ao sistema proporcional.
	 */
	public void foramEleitosMinoritario(){
		int i=0;
		System.out.println("Eleitos, que se beneficiaram do sistema proporcional:");
		System.out.println("(com sua posição no ranking de mais votados)");
		for (Vereador vereador : getListaVereadoresPorVotos()){
			i+=1;
			if (i>eleitos){
				if (vereador.isEleito()){
					if (vereador.getColigacao()==null){
						System.out.println(i+" - "
								+vereador.getNome()+" ("
								+vereador.getPartido().getNome()+", "
								+vereador.getVotos()+" votos)");
					}															//Passa a lista ordenada por voto imprimindo os canditados que 
					else{														//ficaram em posições maiores que a quantidade de vagas, e ainda 
						System.out.println(i+" - "								//assim foram eleitos
								+vereador.getNome()+" ("
								+vereador.getPartido().getNome()+", "
								+vereador.getVotos()+" votos) - Coligação: "
								+vereador.getColigacao().getNome());
					}
				}
			}
		}
		System.out.println();
	}
	/**
	 * Esse método irá utilizar a lista de coligações da classe "EleicaoDeVereadores" para
	 * criar uma nova lista, porém ordenado pela quantidade de votos totais de cada coligação.
	 * @param eleicao Lista com todas as coligações encontradas pelo programa
	 */
	public void ordenaColigacoesPorVotos(EleicaoDeVereadores eleicao){
		Coligacao coligacaoMaisVotado = new Coligacao();
		boolean listaIncompleta = true;
		while (listaIncompleta){
			listaIncompleta = false;
			for (Coligacao coligacao : eleicao.getColigacoes()){
				if (coligacaoMaisVotado.getVotosColigacao()<=coligacao.getVotosColigacao()&&(!(listaColigacoesPorVotos.contains(coligacao)))){
					coligacaoMaisVotado = coligacao;
					listaIncompleta=true;								//Faz a mesma coisa que "ordenaVereadoresPorVotos", porém com as coligações
				}
			}
			if (listaIncompleta==true){
				listaColigacoesPorVotos.add(coligacaoMaisVotado);
				coligacaoMaisVotado = new Coligacao();
			}
		}
		System.out.println();
	}
	
	/**
	 * Utiliza a lista ordenada de coligações para imprimir todas as coligações na ordem de votos.
	 */
	
	public void imprimeListaColigacoes(){
		int i=0;
		System.out.println("Votação (nominal) das coligações e número de candidatos eleitos:");
		for (Coligacao coligacao : getListaColigacoesPorVotos()){
			i+=1;
			if(coligacao.getVereadoresEleitosCol()<=1){
				System.out.println(i+" - Coligação: "
								+coligacao.getNome()+", "
								+coligacao.getVotosColigacao()+" votos, "						//Faz a mesma coisa que a função "vereadoresMaisVotados", porém sem o
								+coligacao.getVereadoresEleitosCol()+" canditado eleito");		//limite na quantidade de itens impressos, além de mudar o jeito impresso
			}																					//dependendo da quantidade de vereadores eleitos (singular ou plural)
			else{
				System.out.println(i+" - Coligação: "
								+coligacao.getNome()+", "
								+coligacao.getVotosColigacao()+" votos, "
								+coligacao.getVereadoresEleitosCol()+" canditados eleitos");
			}
		}
	}

	/**
	 * Esse método irá utilizar a lista de partidos da classe "EleicaoDeVereadores" para
	 * criar uma nova lista, porém ordenado pela quantidade de votos totais de cada partido.
	 * @param eleicao Lista com todos os partidos encontrados pelo programa
	 */
	
	public void ordenaPartidosPorVotos(EleicaoDeVereadores eleicao){
		Partido partidoMaisVotado = new Partido();
		boolean listaIncompleta = true;
		while (listaIncompleta){
			listaIncompleta=false;
			for (Partido partido : eleicao.getPartidos()){
				if (partidoMaisVotado.getVotosTotal()<=partido.getVotosTotal()&&(!(listaPartidosPorVotos.contains(partido)))){
					partidoMaisVotado = partido;
					listaIncompleta=true;									//Novamente mesmo raciocínio que "ordenaVereadoresPorVotos", porém com partidos
				}
			}		
			if (listaIncompleta==true){
					listaPartidosPorVotos.add(partidoMaisVotado);
					partidoMaisVotado = new Partido();
			}
		}
		System.out.println();
	}
	
	/**
	 * Utiliza a lista ordenada de partidos para imprimir todos os partidos na ordem de votos.
	 */
	
	public void imprimeListaPartidos(){
		System.out.println("Votação (nominal) dos partidos e número de candidatos eleitos:");
		int i =0, votos=0;
		for (Partido partido : getListaPartidosPorVotos()){
			i+=1;
			votos += partido.getVotosTotal();
			if (partido.getVereadoresEleitos()<=1){
				System.out.println(i+" - "
						+partido.getNome()+", "
						+partido.getVotosTotal()+" votos, "
						+partido.getVereadoresEleitos()+" canditado eleito");				//Mesmo raciocínio que "imprimeListaColigalcoes"
			}
			else{
				System.out.println(i+" - "
								+partido.getNome()+", "
								+partido.getVotosTotal()+" votos, "
								+partido.getVereadoresEleitos()+" canditados eleitos");
			}
		}
		System.out.println("\nTotal de votos nominais: "+votos);
	}
}
