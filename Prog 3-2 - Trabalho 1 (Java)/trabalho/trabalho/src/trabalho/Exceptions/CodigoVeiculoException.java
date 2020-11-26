package trabalho.Exceptions;
import trabalho.Veiculo;

public class CodigoVeiculoException extends Exception {
	
	public CodigoVeiculoException(){
		super("Código Docente já adicionado");
	}
	
	public CodigoVeiculoException(Veiculo veiculo) {
		super("Código repetido para veículo: " + veiculo.getISSN());
	}
}
