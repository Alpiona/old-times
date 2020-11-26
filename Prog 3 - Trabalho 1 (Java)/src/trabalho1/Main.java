package trabalho1;

import java.io.*;
import java.util.*;

/**
 * Essa classe irá apenas selecionar o arquivo que será lido e utilizar os métodos de outras classes.
 */

public class Main {			
	
	public static void main(String[] args) {
		EleicaoDeVereadores eleicao = new EleicaoDeVereadores();
		String nomeArquivo = args[0];
		File arquivoLeitura = new File (nomeArquivo);
		try{	
			Scanner sc = new Scanner (arquivoLeitura);
			String linha = sc.nextLine();
			while (sc.hasNextLine()){
				linha = sc.nextLine();
				Leitor leitor = new Leitor();
				leitor.pegaInformacaoDaLinha(linha);
				eleicao.novoVereador(leitor);
			}
			eleicao.adicionaColigacoesDeUmPartido();
			sc.close();
				
			Saida saida = new Saida();
			saida.numeroVagas(eleicao);
			saida.ordenaVereadoresPorVotos(eleicao);
			saida.vereadoresEleitos();
			saida.vereadoresMaisVotados();
			saida.seriamEleitosSeMajoritario();
			saida.foramEleitosMinoritario();
			saida.ordenaColigacoesPorVotos(eleicao);
			saida.imprimeListaColigacoes();
			saida.ordenaPartidosPorVotos(eleicao);
			saida.imprimeListaPartidos();
		} catch(FileNotFoundException ex){
            System.out.println(
                    "Não foi possível abrir o arquivo '" +arquivoLeitura + "'"); 
		}
	}
}
