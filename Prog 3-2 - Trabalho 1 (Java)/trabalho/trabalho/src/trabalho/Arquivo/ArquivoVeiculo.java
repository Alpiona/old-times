package trabalho.Arquivo;

import trabalho.Exceptions.*;
import trabalho.Veiculo;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.LinkedList;
import java.util.Scanner;

public class ArquivoVeiculo extends File {

    LinkedList<Veiculo> veiculos = new LinkedList<Veiculo>();
    private String pathname;

    public ArquivoVeiculo(String pathname) throws ExceptionFile {
        super(pathname);
        this.pathname = pathname;
        if (!(new File(pathname).exists())) {
            throw new ExceptionFile();
        }
    }

    public void loadDataToMemory() {
        Scanner sc;
        try {
            sc = new Scanner(this);
            String linha = sc.nextLine();

            while (sc.hasNextLine()) {
                linha = sc.nextLine();
                String[] dados = linha.split(";");
                String sigla = dados[0].trim();

                //Primeiro: Sigla
                String nome = dados[1].trim();
                char tipo;
                try {
                    tipo = isTipoValid(dados[2].charAt(0), sigla); // joga exceção
                    double impacto = Double.parseDouble(dados[3].replace(',', '.'));
                    //Quarto: Fator de impacto
                    String issn = null;            //Quinto: ISSN (caso tenha)
                    if (dados.length > 4) {
                        issn = dados[4];
                    }

                    Veiculo novoVeiculo = new Veiculo(sigla, nome, tipo, impacto, issn);
                    veiculos.add(novoVeiculo);
                } catch (TypeVeiculoNotDefinedException e) {
                    System.out.println(e.getMessage());
                    //(1); // terminar sem gerar arquivo de saída
                }
            }
        } catch (FileNotFoundException e) {
            System.out.println(e.getMessage());
            //(1);
        }
    }

    public LinkedList<Veiculo> getVeiculos() {
        this.loadDataToMemory();
        return veiculos;
    }

    private char isTipoValid(char tipo, String sigla) throws TypeVeiculoNotDefinedException {
        char auxTipo;
        if (tipo == 'P' || tipo == 'C') {
            auxTipo = tipo;
        } else {
            throw new TypeVeiculoNotDefinedException(sigla, tipo);
        }
        return auxTipo;
    }

}
