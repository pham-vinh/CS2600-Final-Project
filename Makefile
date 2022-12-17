CC = gcc
PROGRAM = ./src/tictactoe.c

ifeq ($(OS), Windows_NT)
	DELETE = del
	EXT=.exe
else 
	UNAME_S:=$(shell uname -s)
	ifeq ($(UNAME_S), Darwin)
		DELETE = rm -f
		EXT=.out
	endif
endif

all: build

build:

	$(CC) $(PROGRAM) -lpaho-mqtt3c -o bin/tictactoe$(EXT) 

run: bin/tictactoe$(EXT)
	bin/tictactoe$(EXT)

clean: 
	$(DELETE) bin\*$(EXT)