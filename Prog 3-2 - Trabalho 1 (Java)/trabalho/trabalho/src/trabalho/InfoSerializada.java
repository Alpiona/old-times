package trabalho;
import java.io.Serializable;
import java.util.LinkedList;

public class InfoSerializada implements Serializable {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private LinkedList<Docente> d;
	private LinkedList<Veiculo> v;
	private LinkedList<Publicacao> p;
	private LinkedList<Qualis> q;
	private RegraPontuacao regra;
	
	
	public InfoSerializada(LinkedList<Docente> d, LinkedList<Veiculo> v, LinkedList<Publicacao> p, LinkedList<Qualis> q,
			RegraPontuacao regra) {
		this.d = d;
		this.v = v;
		this.p = p;
		this.q = q;
		this.regra = regra;
	}


	public LinkedList<Docente> getD() {
		return d;
	}


	public LinkedList<Veiculo> getV() {
		return v;
	}


	public LinkedList<Publicacao> getP() {
		return p;
	}


	public LinkedList<Qualis> getQ() {
		return q;
	}


	public RegraPontuacao getRegra() {
		return regra;
	}
	
}
