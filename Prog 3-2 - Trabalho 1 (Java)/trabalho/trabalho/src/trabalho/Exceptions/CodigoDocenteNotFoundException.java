package trabalho.Exceptions;

public class CodigoDocenteNotFoundException extends Exception {

    public CodigoDocenteNotFoundException() {
        super("Exception Sigla Veiculo");
    }

    public CodigoDocenteNotFoundException(String pTitulo, String codigo) {
        super("Código de docente não definido usado na publicação \""
                + pTitulo + "\": " + codigo + ".");
    }
}
