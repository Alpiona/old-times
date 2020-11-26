package trabalho;
import java.util.Date;

public class Qualificacao {
	private Date ano;
	private String siglaVeiculo;
	private String qualis;
	
	public Qualificacao(Date ano, String siglaVeiculo, String qualis) {
		this.ano = ano;
		this.siglaVeiculo = siglaVeiculo;
		this.qualis = qualis;
	}
	
	public Date getAno() {
		return ano;
	}
 }