package trabalho1;

import java.util.*;

/**
 * Essa classe serve para armazenar e trabalhar com as informações adquiridas com a classe "Leitor"
 * 
 */

public class EleicaoDeVereadores {
	
	private LinkedList<Vereador> listaTodosOsVereadores = new LinkedList<Vereador>();
	private LinkedList<Coligacao> listaTodasAsColigacoes = new LinkedList<Coligacao>();
	private LinkedList<Partido> listaTodosOsPartidos = new LinkedList<Partido>();
	
	/**
	 * Esse método cria um novo vereador a cada linha lida do arquivo de entrada, podendo ou não criar novo partido e coligação
	 * depedendo da necessidade.
	 * <P>
	 * É o método principal dessa classe, pois ela chamará todos os outros quando necessário, com exceção de "adicionaColigacoesDeUmPartido".
	 * @param leitor 
	 */
	
	public void novoVereador(Leitor leitor){
		Vereador novoVereador = new Vereador();
		novoVereador.setId(leitor.getId());
		novoVereador.setNome(leitor.getNomeVereador());
		novoVereador.setNum(leitor.getNumero());	
		novoVereador.setVotos(leitor.getVotos());
		novoVereador.setEleito(leitor.isEleito());												
		Partido partido = verificaPartido(leitor);			//Chama método para chamar e criar (se necessário) um partido, para assim
		novoVereador.setPartido(partido);					//o vereador ser adicionado a lista do partido, e o partido adicionado ao vereador
		if (!(leitor.getColigacao()==null)){
			novoVereador.setColigacao(partido.getColigacao());		//Caso o vereador não tenha coligação, fica como null
		}
		partido.getVereadoresDoPartido().add(novoVereador);					
		listaTodosOsVereadores.add(novoVereador);
	}
	
	public LinkedList<Vereador> getTodosOsVereadores() {
		return listaTodosOsVereadores;
	}
	
	public LinkedList<Partido> getPartidos() {
		return listaTodosOsPartidos;
	}
	
	/**
	 * Método para criação de partido, chamado quando não encontra um partido de mesmo nome na lista.
	 * @param leitor 
	 * @return Tipo partido, 
	 */
	
	public Partido criaPartido (Leitor leitor){
		Partido novoPartido = new Partido();
		novoPartido.setNome(leitor.getPartido());
		novoPartido.setVotosTotal(leitor.getVotos());
		if (leitor.isEleito()){
			novoPartido.setVereadoresEleitos(1);
		}
		return novoPartido;
	}
	
	/**
	 * Verifica a existência do partido na lista e se o mesmo possui coligação.
	 * Caso o partido não possua coligação, a variável 'Coligacao' fica como 'null'.
	 * <p>
	 * Caso encontre o partido, e esse partido possui uma coligação, é criado
	 * uma váriavel tipo 'Coligacao' que não é usada, porém necessária para chamar
	 * o método que irá modificar, se necessário, a quantidade de votos e vereadores
	 * eleitos
	 * @param leitor
	 * @return Partido
	 */
	
	public Partido verificaPartido (Leitor leitor){
		boolean existePartido=false;
		Partido novoPartido = new Partido();
		for (Partido partido : listaTodosOsPartidos){
			if (Objects.equals(leitor.getPartido(), partido.getNome())){
				existePartido=true;
				partido.setVotosTotal(partido.getVotosTotal()+leitor.getVotos());
				if (leitor.isEleito()){
					partido.setVereadoresEleitos(partido.getVereadoresEleitos()+1);
				}
				if (!(leitor.getColigacao()==null)){
					Coligacao coligacao = verificaColigacao(leitor);
				}												
				return partido;										
			}
		}
		if (!(existePartido)){
			novoPartido = criaPartido(leitor);
			listaTodosOsPartidos.add(novoPartido);
			if (!(leitor.getColigacao()==null)){
				Coligacao coligacao = new Coligacao();
				coligacao = verificaColigacao(leitor);
				coligacao.getPartidosDaColigacao().add(novoPartido);	
				novoPartido.setColigacao(coligacao);
			}
		}
		return novoPartido;
	}
	
	public LinkedList<Coligacao> getColigacoes(){
		return listaTodasAsColigacoes;
	}
	
	/**
	 * Método para criar novas coligações
	 * @param leitor
	 * @return Nova 'Coligacao' criada
	 */
	public Coligacao criaColigacao (Leitor leitor){
		Coligacao novaColigacao = new Coligacao();
		novaColigacao.setNome(leitor.getColigacao());
		novaColigacao.setVotosColigacao(leitor.getVotos());
		novaColigacao.getPartidosDaColigacao().add(criaPartido(leitor));
		if (leitor.isEleito()){
			novaColigacao.setVereadoresEleitosCol(1);
		}
		return novaColigacao;
	}
	
	/**
	 * Verifica se a coligação já foi criada e adicionada a lista, se tiver sido, é modificado as váriaveis
	 * de votos e vereadores eleitos. Caso contrário é criado uma nova coligação.
	 * 
	 * @param leitor
	 * @return tipo 'Coligacao'
	 */
	public Coligacao verificaColigacao (Leitor leitor){
		boolean existeColigacao = false;
		Coligacao novaColigacao = new Coligacao();
		for (Coligacao coligacao : listaTodasAsColigacoes){
			if (Objects.equals(leitor.getColigacao(), coligacao.getNome())){
				existeColigacao = true;
				coligacao.setVotosColigacao(coligacao.getVotosColigacao()+leitor.getVotos());
				if (leitor.isEleito()){
					coligacao.setVereadoresEleitosCol(coligacao.getVereadoresEleitosCol()+1);
				}
				return coligacao;
			}
		}
		if (!(existeColigacao)){
			novaColigacao = criaColigacao(leitor);
			listaTodasAsColigacoes.add(novaColigacao);
		}
		return novaColigacao;
	}
	
	/**
	 * Esse método foi criado apenas para adicionar os partidos que não possui coligação a lista de coligações.
	 */
	
	public void adicionaColigacoesDeUmPartido (){
		for (Partido partido : listaTodosOsPartidos){
			if (partido.getColigacao()==null){
				Coligacao coligacao = new Coligacao();
				coligacao.setNome (partido.getNome());
				coligacao.getPartidosDaColigacao().add(partido);
				coligacao.setVereadoresEleitosCol(partido.getVereadoresEleitos());
				coligacao.setVotosColigacao(partido.getVotosTotal());
				listaTodasAsColigacoes.add(coligacao);
			}
		}
	}
}

