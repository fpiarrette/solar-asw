# Makefile for cleaning and building

OUTPUT?=./build
SRC?=./src
DEBUG?=1
OPTIMIZATION?=1

ifndef PLATFORM
$(error PLATFORM is not defined!)
endif

# refine variables depending on platform
include platform/$(PLATFORM).mk

ifeq ($(DEBUG),1)
	ARTIFACTS = ${OUTPUT}/${PLATFORM}/debug
	CFLAGS += -g
	CXXFLAGS += -g
else
	ARTIFACTS = ${OUTPUT}/${PLATFORM}/release
endif

ifeq ($(OPTIMIZATION),1)
	CFLAGS += -O2
	CXXFLAGS += -O2
else
	CFLAGS += -O0
	CXXFLAGS += -O0
endif

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
	$(CXX) $(CXXFLAGS) -o $(ARTIFACTS)/main $(FILES) -I$(SRC)
