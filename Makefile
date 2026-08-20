# Makefile for cleaning and building

OUTPUT?=./build
SRC?=./src

ifndef PLATFORM
$(error PLATFORM is not defined!)
endif

ARTIFACTS=${OUTPUT}/${PLATFORM}

FILES=$(SRC)/main.c \
	$(SRC)/utils.c \
	$(SRC)/ChannelSpi.cpp \
	$(SRC)/ChannelSocket.cpp \
	$(SRC)/ChannelSocketServer.cpp \
	$(SRC)/ChannelSocketClient.cpp \
	$(SRC)/Process.cpp \
	$(SRC)/ProcessToModem.cpp \
	$(SRC)/ProcessFromModem.cpp \
	$(SRC)/Signals.cpp \
	$(SRC)/Logger.cpp \
	$(SRC)/LoggerStdout.cpp \
	$(SRC)/LoggerSyslog.cpp \
	$(SRC)/Config.cpp \
	$(SRC)/ContextFromModem.cpp \
	$(SRC)/ContextHost.cpp \
	$(SRC)/ContextToModem.cpp

.PHONY: clean

clean:
	rm -rf $(ARTIFACTS)
	mkdir -p $(ARTIFACTS)

all: $(FILES)
	${CXX} -o $(ARTIFACTS)/main $(FILES) -I$(SRC)
