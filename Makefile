# Makefile for cleaning and building

OUTPUT?=./build
SRC?=./src

.PHONY: clean

clean:
	rm -rf $(OUTPUT)
	mkdir $(OUTPUT)

all: $(SRC)/main.c $(SRC)/tmtc_spi.c $(SRC)/tmtc_socket.c
	${CC} -o $(OUTPUT)/main $(SRC)/main.c $(SRC)/tmtc_spi.c $(SRC)/tmtc_socket.c -I$(SRC)
