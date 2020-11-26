package trabalho.Exceptions;
import java.io.File;

public class ExceptionFile extends Exception {
	private File file;
	
	public ExceptionFile(){
		super("Erro de I/O");
	}

	public ExceptionFile(File file) {
		this.file = file;
	}
	
	public ExceptionFile(String pathname) {
		this.file = new File(pathname);
	}
	
	public String toString() {
		return "Erro de I/O";
	}
}
