package trabalho.Exceptions;

public class TypeVeiculoNotDefinedException extends Exception {
	
	public TypeVeiculoNotDefinedException() {
		super("Erro no tipo veículo");
	}
	
	public TypeVeiculoNotDefinedException(String sigla, char tipo) {
		super("Tipo de veículo desconhecido para veículo " + sigla + ": " + tipo + ".");
	}

}
