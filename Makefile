# Makefile for cleaning and building

OUTPUT?=./build
SRC?=./src

FILES=$(SRC)/main.c \
	$(SRC)/utils.c \
	$(SRC)/ChannelSpi.cpp \
	$(SRC)/ChannelSocket.cpp \
	$(SRC)/Process.cpp \
	$(SRC)/ProcessToModem.cpp \
	$(SRC)/ProcessFromModem.cpp \
	$(SRC)/Signals.cpp \
	$(SRC)/Logger.cpp \
	$(SRC)/LoggerStdout.cpp \
	$(SRC)/LoggerSyslog.cpp

.PHONY: clean

clean:
	rm -rf $(OUTPUT)
	mkdir $(OUTPUT)

all: $(FILES)
	${CXX} -o $(OUTPUT)/main $(FILES) -I$(SRC)
