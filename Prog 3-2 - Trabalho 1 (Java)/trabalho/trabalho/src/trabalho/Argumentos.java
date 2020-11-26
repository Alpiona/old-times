package trabalho;

import java.util.HashMap;
import java.util.Map;

public class Argumentos {
	private String[] args;
	private String[] indicators = new String[6];
	private static String writeOnly= "--write-only";
	private static String readOnly = "--read-only";
	
	Map<String, String> argumentos = new HashMap<String, String>();

	public Argumentos(String[] args) {
		//String[] argumentos = args.split(" -");
		this.args = args;
		if (!this.isWriteOnly()) {
			this.setIndicators();
			this.setArguments();
		}
	}
	
	private void setIndicators() {
		int j = 0;
			int readOnlyPosition = this.getArgumentPosition(readOnly);
			for(int i = 0; i<indicators.length;i++) {
				if(j!=readOnlyPosition) {
					indicators[i] = args[j];
					j = j + 2;
				} else {
					if(readOnlyPosition != -1) {
						indicators[i] = args[j+1];
						j = j + 3;
					}
				}
			}
	}
	
	private void setArguments() {
		for(String indicator : indicators) {
			argumentos.put(indicator, args[this.getArgumentPosition(indicator)+1]);
		}
	}
	
	public boolean isWriteOnly() {
		for(String arg : args) {
			if(arg.equals(writeOnly)) {
				return true;
			}
		}
		return false;
	}
	
	public boolean isReadOnly() {
		for(String arg : args) {
			if(arg.equals(readOnly)) {
				return true;
			}
		}
		return false;
	}
	
	private int getArgumentPosition(String argumento) {
		int i = 0;
		for(String arg: args) {
			if(arg.equals(argumento)) {
				return i;
			}
			i++;
		}
		return -1;
	}
	
	public String getPathnameArquivoDocente() {
		return argumentos.get("-d");
	}
	
	public String getPathnameArquivoVeiculo() {
		return argumentos.get("-v");
	}
	
	public String getPathnameArquivoPublicacoes() {
		return argumentos.get("-p");
	}
	
	public String getPathnameArquivoRegras() {
		return argumentos.get("-r");
	}
	
	public String getPathnameArquivoQualis() {
		return argumentos.get("-q");
	}
	
	public String getNomeArquivo(String c) {
		return argumentos.get(c);
	}
	
}
