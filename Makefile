BIN = bin
SRC = src

INCLUDE = -I$(SRC)/common

CXX = g++
CC = gcc

LDFLAGS = -lm -lGL -lX11

WARNINGS = -Wall -Wextra -W -pedantic

CXXFLAGS = -g -DGL_GLEXT_PROTOTYPES $(WARNINGS) `sdl-config --cflags` -std=c++0x $(INCLUDE)
CFLAGS = -g -DGL_GLEXT_PROTOTYPES $(WARNINGS) `sdl-config --cflags` -std=c99 $(INCLUDE)

CXXSOURCES = $(wildcard $(SRC)/*.cpp)
CSOURCES = $(wildcard $(SRC)/*.c)

COBJ = $(patsubst $(SRC)/%.c,$(BIN)/%.o, $(CSOURCES))
CXXOBJ = $(patsubst $(SRC)/%.cpp,$(BIN)/%.o, $(CXXSOURCES))

OBJ = $(COBJ) $(CXXOBJ)

.PHONY: all clean cleanall src bin

EXE = program

all: bin src $(EXE)

$(BIN)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $? -o $@

$(BIN)/%.o: $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) -c $? -o $@

program: $(OBJ)
	echo $(COBJ)
	echo $(CXXSOURCES)
	$(CXX) $^ -o $@ $(LDFLAGS)

src:
	mkdir -p src/

bin:
	mkdir -p bin/

clean:
	rm $(OBJ)

cleanall:
	rm $(OBJ) $(EXE)
