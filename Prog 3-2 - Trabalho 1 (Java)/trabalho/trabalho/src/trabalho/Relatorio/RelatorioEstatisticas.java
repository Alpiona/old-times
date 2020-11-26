package trabalho.Relatorio;

import java.io.FileWriter;
import java.io.IOException;
import java.util.LinkedList;
import java.util.Locale;
import trabalho.Publicacao;

public class RelatorioEstatisticas {
	private LinkedList<Publicacao> publicacoes;
	private String pathname;
	
	// Qualis Static List
	private static final String[] categoriasQualis = {"A1","A2","B1","B2","B3","B4","B5","C"};
	private LinkedList<EstatisticaQualis> estatisticas = new LinkedList<EstatisticaQualis>();
	// File Writer
	private static final String COMMA_DELIMITER = ";";
	private static final String NEW_LINE_SEPARATOR = "\n";
	private static final String FILE_HEADER = "Qualis;Qtd. Artigos;Média Artigos / Docente";

	
	public RelatorioEstatisticas(String pathname, LinkedList<Publicacao> publicacoes) {
		this.pathname = pathname;
		this.publicacoes = publicacoes;
		this.getEstatisticaAllQualis();
	}
	
	private void getEstatisticaAllQualis() {
		for(String qualis: categoriasQualis) {
			this.getEstatisticasDeQualis(qualis);
		}
	}
	
	private void getEstatisticasDeQualis(String qualis) {
		int auxNArtigos = 0;
		double nArtigosPorDocente = 0;
		for(Publicacao p : publicacoes) {
			if(p.getQualis().equals(qualis)) {
				auxNArtigos++;
				double auxNArtigosPorDocente = 1.0 / p.getAutores().size();
				nArtigosPorDocente = nArtigosPorDocente + auxNArtigosPorDocente;
			}
		}
		estatisticas.add(new EstatisticaQualis(qualis, auxNArtigos, nArtigosPorDocente));
	}
	
	public void write() {
		FileWriter fileWriter = null;
		
		try {
			// Definindo Brasil como padrão para double
			
			Locale localeBrasil = new Locale("pt", "BR");
			fileWriter = new FileWriter(pathname);
			fileWriter.append(FILE_HEADER.toString());
			fileWriter.append(NEW_LINE_SEPARATOR.toString());
			
			for(EstatisticaQualis e : this.estatisticas) {
				fileWriter.append(e.getQualis());
				fileWriter.append(COMMA_DELIMITER.toString());
				fileWriter.append(String.valueOf(e.getNArtigos()));
				fileWriter.append(COMMA_DELIMITER.toString());
				fileWriter.append(String.format(localeBrasil,"%.2f", e.returnArtigosPorDocente()));
				fileWriter.append(NEW_LINE_SEPARATOR.toString());
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

class EstatisticaQualis {
	private String qualis;
	private int nArtigos;
	private double nArtigosPorDocente;
	
	public EstatisticaQualis(String qualis, int nArtigos, double nArtigosPorDocente) {
		this.qualis = qualis;
		this.nArtigos = nArtigos;
		this.nArtigosPorDocente = nArtigosPorDocente;
	}
	
	public String getQualis() {
		return qualis;
	}
	
	public int getNArtigos() {
		return nArtigos;
	}
	
	public double returnArtigosPorDocente() {
		return nArtigosPorDocente;
	}
}

