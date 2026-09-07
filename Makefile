# Makefile for cleaning and building

OUTPUT?=./build
SRC?=./src
DEBUG?=1
OPTIMIZATION?=1
HARDENING?=0

ifndef PLATFORM
$(error PLATFORM is not defined!)
endif

# configure variables values depending on platform
include platform/$(PLATFORM).mk

# for any platform...
CFLAGS += -Wfatal-errors -Wall -std=c99 -DPLATFORM=$(PLATFORM)
CXXFLAGS += -Wfatal-errors -Wall -std=c++11 -DPLATFORM=$(PLATFORM)
LDLIBS += -lmicrohttpd

# Manage DEBUG options
ifeq ($(DEBUG),1)
	ARTIFACTS = ${OUTPUT}/${PLATFORM}/debug
	CFLAGS += -g -feliminate-unused-debug-types -DDEBUG
	CXXFLAGS += -g -feliminate-unused-debug-types -DDEBUG
else
	ARTIFACTS = ${OUTPUT}/${PLATFORM}/release
	CFLAGS += -DNDEBUG
	CXXFLAGS += -DNDEBUG
endif

# Manage optimizations
ifeq ($(OPTIMIZATION),1)
	CFLAGS += -O2
	CXXFLAGS += -O2
else
	CFLAGS += -O0
	CXXFLAGS += -O0
endif

# For hardening consider using....
# -Wl,-z,now
# -Wl,-z,relro
# -Wl,-z,noexecstack
ifeq ($(HARDENING),1)
	CFLAGS += -fstack-protector -fstack-protector-strong -Wformat -Wformat-security -Werror=format-security
	CXXFLAGS += -fstack-protector -fstack-protector-strong -Wformat -Wformat-security -Werror=format-security
	ifeq ($(OPTIMIZATION),1)
		CFLAGS += -D_FORTIFY_SOURCE=2
		CXXFLAGS += -D_FORTIFY_SOURCE=2
	endif
endif

FILES=$(SRC)/main.c \
	$(SRC)/Alarms.cpp \
	$(SRC)/utils.c \
	$(SRC)/ChannelNull.cpp \
	$(SRC)/ChannelSpi.cpp \
	$(SRC)/ChannelSocket.cpp \
	$(SRC)/ChannelSocketServer.cpp \
	$(SRC)/ChannelSocketClient.cpp \
	$(SRC)/CircularBuffer.cpp \
	$(SRC)/Gpio.cpp \
	$(SRC)/GpioMock.cpp \
	$(SRC)/GpioModule.cpp \
	$(SRC)/platform/$(PLATFORM)/Platform.cpp \
	$(SRC)/Signals.cpp \
	$(SRC)/Scheduller.cpp \
	$(SRC)/Logger.cpp \
	$(SRC)/LoggerAbstract.cpp \
	$(SRC)/LoggerStdout.cpp \
	$(SRC)/LoggerSyslog.cpp \
	$(SRC)/Config.cpp \
	$(SRC)/TaskFromModem.cpp \
	$(SRC)/TaskHumanInterface.cpp \
	$(SRC)/TaskIdle.cpp \
	$(SRC)/TaskKiller.cpp \
	$(SRC)/TaskRest.cpp \
	$(SRC)/TaskToModem.cpp


.PHONY: clean

clean:
	rm -rf $(ARTIFACTS)
	mkdir -p $(ARTIFACTS)

all: $(FILES)
	$(CXX) $(CXXFLAGS) $(FILES) -I$(SRC) $(LDFLAGS) $(LDLIBS) -o $(ARTIFACTS)/main
