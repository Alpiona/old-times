package trabalho.Arquivo;

import trabalho.Exceptions.*;
import trabalho.Qualis;
import trabalho.RegraPontuacao;
import trabalho.Veiculo;
import java.util.LinkedList;
import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;

public class ArquivoQualificacoes extends File {

    private LinkedList<Qualis> qualificacoes = new LinkedList<Qualis>();
    private LinkedList<Veiculo> veiculos = new LinkedList<Veiculo>();
    private LinkedList<Veiculo> novoVeiculos = new LinkedList<Veiculo>();
    private RegraPontuacao regra;

    public ArquivoQualificacoes(String pathname, LinkedList<Veiculo> veiculos) throws ExceptionFile {
        super(pathname);
        this.veiculos = veiculos;
        if (!this.exists()) {
            throw new ExceptionFile();
        }
        this.loadToLocalMemory();
    }

    public void loadToLocalMemory() {
        Scanner sc;
        try {
            sc = new Scanner(this);
            String linha = sc.nextLine();

            //Novamente lê as linhas
            while (sc.hasNextLine()) {
                linha = sc.nextLine();
                String[] dados = linha.split(";");
                int ano = Integer.parseInt(dados[0]);           //Primeiro: ano
                String siglaVeiculo = dados[1].trim();                 //Segundo: Sigla do veículo
                String qualis = dados[2];
                //Terceiro: Classificação Qualis

                Qualis novoQualis = new Qualis(ano, qualis);
                qualificacoes.add(novoQualis);

                try {
                    Veiculo v = this.getVeiculoWithSigla(ano, siglaVeiculo);
                    try {
                        this.isValidQualis(novoQualis, siglaVeiculo);
                        v.getListaQualis().add(novoQualis);
                        novoVeiculos.add(v);
                    } catch (QualisNotFoundException e) {
                        System.out.println(e.getMessage());
                        //(1);
                    }
                } catch (SiglaVeiculoNotFoundException e) {
                    System.out.println(e.getMessage());
                    //(1);
                }

                //O 'Qualis' é criado e adicionado na lista geral, em seguida é encontrado o veículo com a mesma sigla e o qualis é atribuido a lista de qualis do veículo
            }
        } catch (FileNotFoundException e) {
            System.out.println(e.getMessage());
            //(1);
        }
    }

    public Veiculo getVeiculoWithSigla(int ano, String sigla) throws SiglaVeiculoNotFoundException {
        Veiculo returnedVeiculo = null;
        for (Veiculo auxVeiculo : veiculos) {
            if (auxVeiculo.getSigla().equals(sigla)) {
                returnedVeiculo = auxVeiculo;
            }
        }

        if (returnedVeiculo == null) {
            throw new SiglaVeiculoNotFoundException(ano, sigla);
        }

        return returnedVeiculo;
    }

    public boolean isValidQualis(Qualis qualis, String vSigla) throws QualisNotFoundException {
        boolean isValidQualis = true;
        if (!qualis.isValidQualis()) {
            isValidQualis = false;
            throw new QualisNotFoundException(vSigla, qualis.getAno(), qualis.getQualis());
        }
        return isValidQualis;
    }

    public LinkedList<Qualis> getQualis() {
        return qualificacoes;
    }

    public LinkedList<Veiculo> getVeiculosModificados() {
        return novoVeiculos;
    }

    public void setRegra(RegraPontuacao regra) {
        this.regra = regra;
        this.colocarPontuacaoQualis();
    }

    private void colocarPontuacaoQualis() {
        for (Qualis auxQualis : qualificacoes) {
            auxQualis.setPontuacao(regra.valorQualis(auxQualis.getQualis()));
        }
    }

}
