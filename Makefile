# Makefile for cleaning and building

.PHONY: clean

clean:
	rm -rf ./build
	mkdir ./build

all: ./src/main.c ./src/module.c
	${CC} -o ./build/main ./src/main.c ./src/module.c -I./src
