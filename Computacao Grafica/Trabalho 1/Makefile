CC=g++
CFLAGS=-c -std=c++11 -Wall
LDFLAGS=
FLAGS= -lGL -lGLU -lglut
SRC_PATH=data
VPATH=${SRC_PATH}
SOURCES= trabalho1.cpp tinyxml2.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=trabalhocg
BINDIR=


all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(FLAGS)

run:
	@./$(EXECUTABLE)
clean:
	rm *.o
