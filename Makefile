# Makefile for cleaning and building

DEBUG?=1
OPTIMIZATION?=1
HARDENING?=0

ifndef SRC_DIR
$(error SRC_DIR is not defined!)
endif

ifndef BINARY_NAME
$(error BINARY_NAME is not defined!)
endif

ifndef PLATFORM
$(error PLATFORM is not defined!)
endif

ifndef OUTPUT_DIR
$(error OUTPUT_DIR is not defined!)
endif

ifndef PLATFORM_ID
$(error PLATFORM_ID is not defined!)
endif

ifndef PLATFORM_HOST
$(error PLATFORM_HOST is not defined!)
endif

ifndef PLATFORM_TARGET
$(error PLATFORM_TARGET is not defined!)
endif

# configure variables values depending on platform
include config/make/$(PLATFORM).mk

# for any platform...
CFLAGS += -Wfatal-errors -Wall -std=c99 -DPLATFORM=$(PLATFORM) -DPLATFORM_ID=$(PLATFORM_ID) -DPLATFORM_HOST=$(PLATFORM_HOST) -DPLATFORM_TARGET=$(PLATFORM_TARGET)
CXXFLAGS += -Wfatal-errors -Wall -std=c++11 -DPLATFORM=$(PLATFORM) -DPLATFORM_ID=$(PLATFORM_ID) -DPLATFORM_HOST=$(PLATFORM_HOST) -DPLATFORM_TARGET=$(PLATFORM_TARGET)
LDLIBS += -lmicrohttpd

# Manage DEBUG options
ifeq ($(DEBUG),1)
	CFLAGS += -g -feliminate-unused-debug-types -DDEBUG
	CXXFLAGS += -g -feliminate-unused-debug-types -DDEBUG
else
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

FILES=$(SRC_DIR)/main.c \
	$(SRC_DIR)/Alarms.cpp \
	$(SRC_DIR)/utils.c \
	$(SRC_DIR)/ChannelNull.cpp \
	$(SRC_DIR)/ChannelSpi.cpp \
	$(SRC_DIR)/ChannelSocket.cpp \
	$(SRC_DIR)/ChannelSocketServer.cpp \
	$(SRC_DIR)/ChannelSocketClient.cpp \
	$(SRC_DIR)/CircularBuffer.cpp \
	$(SRC_DIR)/Gpio.cpp \
	$(SRC_DIR)/GpioMock.cpp \
	$(SRC_DIR)/GpioModule.cpp \
	$(SRC_DIR)/platform/$(PLATFORM)/Platform.cpp \
	$(SRC_DIR)/Signals.cpp \
	$(SRC_DIR)/Scheduller.cpp \
	$(SRC_DIR)/Logger.cpp \
	$(SRC_DIR)/LoggerAbstract.cpp \
	$(SRC_DIR)/LoggerStdout.cpp \
	$(SRC_DIR)/LoggerSyslog.cpp \
	$(SRC_DIR)/Config.cpp \
	$(SRC_DIR)/TaskFromModem.cpp \
	$(SRC_DIR)/TaskHumanInterface.cpp \
	$(SRC_DIR)/TaskIdle.cpp \
	$(SRC_DIR)/TaskKiller.cpp \
	$(SRC_DIR)/TaskToModem.cpp

FILES_TEST_SPI=$(SRC_DIR)/test_spi.c \
	$(SRC_DIR)/ChannelSpi.cpp \
	$(SRC_DIR)/Logger.cpp \
	$(SRC_DIR)/LoggerAbstract.cpp \
	$(SRC_DIR)/LoggerStdout.cpp \
	$(SRC_DIR)/LoggerSyslog.cpp

FILES_TEST_GPIO=$(SRC_DIR)/test_gpio.c \
	$(SRC_DIR)/Gpio.cpp \
	$(SRC_DIR)/GpioMock.cpp \
	$(SRC_DIR)/GpioModule.cpp \
	$(SRC_DIR)/Logger.cpp \
	$(SRC_DIR)/LoggerAbstract.cpp \
	$(SRC_DIR)/LoggerStdout.cpp \
	$(SRC_DIR)/LoggerSyslog.cpp

FILES_TEST_GPIO_IOCTL=$(SRC_DIR)/test_gpio_ioctl.c

FILES_TEST_SPI_IOCTL=$(SRC_DIR)/test_spi_ioctl.c

.PHONY: clean

clean:
	rm -rf $(OUTPUT_DIR)
	mkdir -p $(OUTPUT_DIR)

all: $(FILES)
	$(CXX) $(CXXFLAGS) $(FILES) -I$(SRC_DIR) $(LDFLAGS) $(LDLIBS) -o $(OUTPUT_DIR)/$(BINARY_NAME)

tests: test_spi test_spi_ioctl test_gpio test_gpio_ioctl

test_spi: $(FILES_TEST_SPI)
	$(CXX) $(CXXFLAGS) $(FILES_TEST_SPI) -I$(SRC_DIR) $(LDFLAGS) $(LDLIBS) -o $(OUTPUT_DIR)/test_spi

test_spi_ioctl: $(FILES_TEST_SPI_IOCTL)
	$(CXX) $(CXXFLAGS) $(FILES_TEST_SPI_IOCTL) -I$(SRC_DIR) $(LDFLAGS) $(LDLIBS) -o $(OUTPUT_DIR)/test_spi_ioctl

test_gpio: $(FILES_TEST_GPIO)
	$(CXX) $(CXXFLAGS) $(FILES_TEST_GPIO) -I$(SRC_DIR) $(LDFLAGS) $(LDLIBS) -o $(OUTPUT_DIR)/test_gpio

test_gpio_ioctl: $(FILES_TEST_GPIO_IOCTL)
	$(CXX) $(CXXFLAGS) $(FILES_TEST_GPIO_IOCTL) -I$(SRC_DIR) $(LDFLAGS) $(LDLIBS) -o $(OUTPUT_DIR)/test_gpio_ioctl
