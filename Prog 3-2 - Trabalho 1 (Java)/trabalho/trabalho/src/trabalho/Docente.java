package trabalho;

import java.util.Date;
import java.io.Serializable;
import java.util.*;

public class Docente implements Serializable{

    /**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	private long codigo;
    private String nome;
    private Date dataNascimento;
    private Date dataIngresso;
    private boolean coordenador;
    private LinkedList<Publicacao> publicacoes = new LinkedList<Publicacao>();

    public Docente(long codigo, String nome, Date dataNascimento, Date dataIngresso,
            boolean coordenador) {
        this.codigo = codigo;
        this.nome = nome;
        this.dataNascimento = dataNascimento;
        this.dataIngresso = dataIngresso;
        this.coordenador = coordenador;
    }

    public long getCodigo() {
        return codigo;
    }

    public String getNome() {
        return nome;
    }

    public Date getDataNascimento() {
        return dataNascimento;
    }

    public Date getDataIngresso() {
        return dataIngresso;
    }

    public boolean isCoordenador() {
        return coordenador;
    }

    public LinkedList<Publicacao> getPublicacoes() {
        return publicacoes;
    }

    public void adicionarPublicacao(Publicacao publicacao) {
        publicacoes.add(publicacao);
    }

    public String toString() {
        return nome;
    }

}
