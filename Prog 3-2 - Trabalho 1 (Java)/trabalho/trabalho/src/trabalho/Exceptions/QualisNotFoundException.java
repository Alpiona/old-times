package trabalho.Exceptions;

public class QualisNotFoundException extends Exception {

	public QualisNotFoundException(String vSigla,int ano, String qualis) {
		super("Qualis desconhecido para qualificação do veículo " + vSigla + " no ano "
				+ ano + ": " + qualis + ".");
	}
	
	public QualisNotFoundException(int ano, String qualis) {
		super("Qualis desconhecido para regras de 01/01/" + ano + ": " + qualis);
	}
}
