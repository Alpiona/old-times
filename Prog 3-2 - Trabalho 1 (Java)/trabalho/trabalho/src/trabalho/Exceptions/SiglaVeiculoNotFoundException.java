package trabalho.Exceptions;

import trabalho.Veiculo;

public class SiglaVeiculoNotFoundException extends Exception {

	public SiglaVeiculoNotFoundException(){
		super("Exception Sigla Veiculo");
	}
	
	public SiglaVeiculoNotFoundException(String pTitulo, String vSigla) {
		super("Sigla de veículo não definida usada na publicação \"" +
				pTitulo + "\": " + vSigla + ".");
	}
	
	public SiglaVeiculoNotFoundException(int ano, String sigla) {
		super("Sigla de veículo não definida usada na qualificação do ano \"" + ano + "\": " + sigla + ".");
	}
}
