# Makefile for cleaning and building

OUTPUT?=./build
SRC?=./src

.PHONY: clean

clean:
	rm -rf $(OUTPUT)
	mkdir $(OUTPUT)

all: $(SRC)/main.c $(SRC)/tmtc_spi.c $(SRC)/tmtc_socket.c $(SRC)/utils.c $(SRC)/ChannelSpi.cpp $(SRC)/ChannelSocket.cpp $(SRC)/ProcessToModem.cpp $(SRC)/ProcessFromModem.cpp
	${CXX} -o $(OUTPUT)/main $(SRC)/main.c $(SRC)/tmtc_spi.c $(SRC)/tmtc_socket.c $(SRC)/utils.c $(SRC)/ChannelSpi.cpp $(SRC)/ChannelSocket.cpp $(SRC)/ProcessToModem.cpp $(SRC)/ProcessFromModem.cpp -I$(SRC)
