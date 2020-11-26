CC=g++
CFLAGS=-c -std=c++11 -Wall
LDFLAGS=
FLAGS=
SRC_PATH=data
VPATH=${SRC_PATH}
SOURCES= Main.cpp Docente.cpp ArquivoDocente.cpp Publicacao.cpp ArquivoPublicacoes.cpp PublicacaoConferecia.cpp PublicacaoPeriodico.cpp Qualis.cpp ArquivoQualificacoes.cpp Veiculo.cpp ArquivoVeiculo.cpp RegraPontuacao.cpp ArquivoRegras.cpp ExceptionFile.cpp util/DateUtils.cpp util/NumberUtils.cpp util/NumPunctPTBR.cpp util/StringUtils.cpp util/Tokenizer.cpp RelatorioPublicacao.cpp RelatorioEstatisticas.cpp RelatorioRecredenciamento.cpp Argumento.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=trab
BINDIR=


all: $(SOURCES) $(EXECUTABLE)
        
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(FLAGS)
	rm *.o

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ $(FLAGS)

run:
	@./$(EXECUTABLE) -d docentes.csv -v veiculos.csv -p publicacoes.csv -q qualis.csv -r regras.csv -a 2017

clean: trab
	rm *.o $(EXECUTABLE)

install:
	#install -s $(EXECUTABLE) $(BINDIR)
	sudo cp -u $(EXECUTABLE) $(BINDIR)
uninstall:
	sudo rm $(BINDIR)/$(EXECUTABLE)

