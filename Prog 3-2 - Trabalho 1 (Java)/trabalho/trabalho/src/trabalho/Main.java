package trabalho;

import java.io.*;
import java.text.*;
import java.util.*;
import trabalho.Arquivo.*;
import trabalho.Exceptions.*;
import trabalho.Relatorio.*;

public class Main {

    /*
	 * FUNÇÃO MAIN
	 * Falta: impementar argumentos para nome de arquivos de entrada
     */
    private static LinkedList<Docente> docentes = new LinkedList<Docente>();
    private static LinkedList<Publicacao> publicacoes = new LinkedList<Publicacao>();
    private static LinkedList<Qualis> listaQualis = new LinkedList<Qualis>();
    private static LinkedList<Veiculo> veiculos = new LinkedList<Veiculo>();
    private static RegraPontuacao regra;

    public static void main(String[] args) {
    	
    	/*
    	 * Manipulando argumentos
    	 */
    	
    	Argumentos arg = new Argumentos(args);

        /*
    	 * Caso não seja --read-only ou --write-only
    	 * ler arquivos CSV e gerar os relatórios normalmente
         */
        
    	if(!arg.isReadOnly() && !arg.isWriteOnly()) {
        	lerArquivosEntrada(arg);
        	gerarRelatorios();
        }

        /* 
		 * Caso seja --read-only
		 * Ler os arquivos CSV e serializar a informação em recredenciamento.dat
         */
        
        if(arg.isReadOnly()) {
        	lerArquivosEntrada(arg);
        	InfoSerializada info = new InfoSerializada(docentes, veiculos, publicacoes, listaQualis, regra);
        	 try {
        		 FileOutputStream fileRecredenciamento = new FileOutputStream("recredenciamento.dat");
        		 ObjectOutputStream oo = new ObjectOutputStream(fileRecredenciamento);
        		 oo.writeObject(info);
        	 } catch(Exception e) {
        		 System.out.println(e.getMessage());
        	 }
        }
        
        /*
         * Caso seja write-only:
         * Ler apenas o arquivo recredenciamento.dat e gerar os relatórios a partir
         * desse arquivo com as informações serializadas
         */
        
        if(arg.isWriteOnly()) {
        	try {
        		FileInputStream fileDeserializarRec = new FileInputStream("recredenciamento.dat");
        		ObjectInputStream doc = new ObjectInputStream(fileDeserializarRec);
        		InfoSerializada info = (InfoSerializada) doc.readObject();
        		
        		publicacoes = (LinkedList<Publicacao>) info.getP();
        		veiculos = (LinkedList<Veiculo>) info.getV();
        		listaQualis = (LinkedList<Qualis>) info.getQ();
        		docentes = (LinkedList<Docente>) info.getD();
        		regra = (RegraPontuacao) info.getRegra();
        		gerarRelatorios();
        		
        	} catch(Exception e) {
        		System.out.println(e.getMessage());
        	}
        }
        
    }
    
    private static void lerArquivosEntrada(Argumentos arg) {
    	ArquivoDocente arqDocente;
        ArquivoVeiculo arqVeiculo;
        ArquivoPublicacoes arqPublicacoes;
        ArquivoQualificacoes arqQualificacoes;
        ArquivoRegras arqRegras;

        /*
    	 * Criando os arquivos:
    	 * Tratando as Exceções de I/O caso o arquivo não exista
    	 * Substituir posteriormente pelos argumentos
         */
        try {
            arqDocente = new ArquivoDocente(arg.getPathnameArquivoDocente());
            docentes = arqDocente.getDocentes();
        } catch (ExceptionFile e) {
            printAndStop(e.getMessage());
        }

        try {
            arqVeiculo = new ArquivoVeiculo(arg.getPathnameArquivoVeiculo());
            veiculos = arqVeiculo.getVeiculos();
        } catch (ExceptionFile e) {
            printAndStop(e.getMessage());
        }

        try {
            arqPublicacoes = new ArquivoPublicacoes(arg.getPathnameArquivoPublicacoes(), docentes, veiculos);
            publicacoes = arqPublicacoes.getPublicacoes();
        } catch (ExceptionFile e) {
            printAndStop(e.getMessage());
        }

        try {
            arqRegras = new ArquivoRegras(arg.getPathnameArquivoRegras());
            regra = arqRegras.getRegra();
        } catch (ExceptionFile e) {
            printAndStop(e.getMessage());
        }

        try {
            arqQualificacoes = new ArquivoQualificacoes(arg.getPathnameArquivoQualis(), veiculos);
            arqQualificacoes.setRegra(regra);
            listaQualis = arqQualificacoes.getQualis();
        } catch (ExceptionFile e) {
            printAndStop(e.getMessage());
        }
    }
    
    private static void gerarRelatorios() {
    	RelatorioPublicacoes rPublicacoes = new RelatorioPublicacoes("2-publicacoes.csv", publicacoes);
        rPublicacoes.write();

        //Utilizando publicações ordenadas do relatório 2 para o relatório 3
        LinkedList<Publicacao> publicacoesOrdenadas = rPublicacoes.ordenar();

        RelatorioEstatisticas rEstatisticas = new RelatorioEstatisticas("3-estatisticas.csv", publicacoesOrdenadas);
        rEstatisticas.write();

        RelatorioRecredenciamento rRecredenciamento = new RelatorioRecredenciamento("1-recredenciamento.csv", docentes, regra);
        rRecredenciamento.write();
    }

    // Função auxiliar para printar na tela e parar a Main Thread
    public static void printAndStop(String s) {
        System.out.println(s);
        //(1);
    }
}
