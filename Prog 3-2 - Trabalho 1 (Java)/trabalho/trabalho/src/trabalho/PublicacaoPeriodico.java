package trabalho;
import java.io.Serializable;
import java.util.LinkedList;

public class PublicacaoPeriodico extends Publicacao implements Serializable{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private int volume;

	public PublicacaoPeriodico() {
		super();
	}

	public PublicacaoPeriodico(int numero, int ano, int volume, int pgInicial, int pgFinal, String titulo,
			Veiculo veiculo, LinkedList<Docente> autores) {
		super(numero, ano, pgInicial, pgFinal, titulo, veiculo, autores);
		this.volume = volume;
	}
	
	public int getVolume() {
		return volume;
	}
}
