package trabalho;
import java.io.Serializable;
import java.util.LinkedList;

public class PublicacaoConferencia extends Publicacao implements Serializable{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private String local;

	public PublicacaoConferencia() {
		super();
	}

	public PublicacaoConferencia(int numero, int ano, int pgInicial, int pgFinal, String titulo, Veiculo veiculo,
			String local, LinkedList<Docente> autores) {
		super(numero, ano, pgInicial, pgFinal, titulo, veiculo, autores);
		this.local = local;
	}
        
        public String getLocal(){
            return local;
        }
}
