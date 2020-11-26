package trabalho.Arquivo;

import java.io.File;
import java.io.FileNotFoundException;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Objects;
import java.util.Scanner;

import trabalho.RegraPontuacao;
import trabalho.Exceptions.ExceptionFile;
import trabalho.Exceptions.QualisNotFoundException;

public class ArquivoRegras extends File {

    static DateFormat format = new SimpleDateFormat("dd/MM/yyyy");
    private RegraPontuacao regra = new RegraPontuacao();

    public ArquivoRegras(String pathname) throws ExceptionFile {
        super(pathname);
        if (!this.exists()) {
            throw new ExceptionFile();
        }
    }

    public void loadDataToLocalMemory() {
        Scanner sc;
        try {
            sc = new Scanner(this);
            String linha = sc.nextLine();
            String[] todosQualis = {"A1", "A2", "B1", "B2", "B3", "B4", "B5", "C"};        //Lista usado como base para as classificações
            linha = sc.nextLine();
            String[] dados = linha.split(";");
            Date inicioVigencia = new Date();
            Date fimVigencia = new Date();

            // Pegando apenas o ano início vigência
            String dataInicioVigencia[] = dados[0].split("/");
            int anoInicioVigencia = Integer.parseInt(dataInicioVigencia[dataInicioVigencia.length - 1]);

            try {
                inicioVigencia = format.parse(dados[0]);        //Primeiro: Data de início
                fimVigencia = format.parse(dados[1]);           //Segundo: Data final
            } catch (ParseException ex) {
                System.out.println("Erro de formatação");
            }
            String[] categoriasQualis;    
            categoriasQualis = dados[2].split(",");         //Terceiro: Classificações (Dividido em string usando a ',' como divisor
            String[] auxString = dados[3].split(",");       //Quarto: Pontuação das classificações (Divide igual o anterior)
            int[] pontuacaoQualis = new int[8];  

            for (String auxQualis : categoriasQualis) {
                try {
                    if (this.isQualisValid(anoInicioVigencia, todosQualis, auxQualis)) {
                        for (int i = 0; i < categoriasQualis.length;) {
                            for (int j = 0; j < 8;) {
                                if (Objects.equals(categoriasQualis[i], todosQualis[j])) {
                                    pontuacaoQualis[j] = Integer.parseInt(auxString[i].trim());
                                    i++;
                                    j++;
                                } else {
                                    pontuacaoQualis[j] = Integer.parseInt(auxString[i - 1].trim());
                                    j++;
                                }
                            }
                        }

                        dados[4] = dados[4].replace(",", ".");                          //Muda ',' para '.' para ser reconhecido como um número
                        double multiplicador = Double.parseDouble(dados[4].trim());     //Quinto: Multiplicador
                        int anos = Integer.parseInt(dados[5].trim());                   //Sexto: Anos
                        int pontuacaoMin = Integer.parseInt(dados[6].trim());           //Sétimo: Pontuação mínima
                        regra = new RegraPontuacao(inicioVigencia, fimVigencia, pontuacaoQualis, multiplicador, anos, pontuacaoMin);
                    }

                } catch (QualisNotFoundException e) {
                    System.out.println(e.getMessage());
                }
            }

            //O 'for' é para adicionar a pontuação das classificações que não estão na lista, comparando com a lista base criado no começo da função
        } catch (FileNotFoundException e) {
            System.out.println("Erro de I/O");
        }
    }

    public boolean isQualisValid(int ano, String[] todasQualis, String qualis) throws QualisNotFoundException {
        boolean valid = false;
        for (String auxQualis : todasQualis) {
            if (auxQualis.equals(qualis)) {
                valid = true;
            }
        }

        if (!valid) {
            throw new QualisNotFoundException(ano, qualis);
        }

        return valid;
    }

    public RegraPontuacao getRegra() {
        this.loadDataToLocalMemory();
        return regra;
    }

}
