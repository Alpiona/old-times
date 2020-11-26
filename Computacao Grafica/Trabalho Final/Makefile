CC=g++
CFLAGS=-c -std=c++11 -Wall
LDFLAGS=
FLAGS= -lGL -lGLU -lglut
SRC_PATH=data
VPATH=${SRC_PATH}
SOURCES= tf.cpp tinyxml2.cpp personagem.cpp projetil.cpp objeto.cpp objloader.cpp imageloader.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=trabalhocg
BINDIR=


all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(FLAGS)

.cpp.o:
		$(CC) $(CFLAGS) $< -o $@ $(FLAGS)

run:
	@./$(EXECUTABLE)
clean:
	rm *.o
