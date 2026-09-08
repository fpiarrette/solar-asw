# Originally, AK Nord SDK for XT ATTO LXL, delivered as a zip/tar, has been installed in a Docker image. This installation,
# counts with a script that prepares SDK to be used. This script is sourced each time Docker container is executed, by means
# of a shell script that serves as ENTRY POINT. After SDK configuration script is sourced, several environments variables are
# defined. In particular, CC and CXX, that contains the  full C/C++ compiler name, it means prefix plus gcc or g++, om top of
# a set of flags. Default values are:
#
# CC = arm-poky-linux-gnueabi-gcc -mthumb -mfpu=neon-vfpv4 -mfloat-abi=hard -mcpu=cortex-a5 -fstack-protector-strong -O2
#		-D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security -D_TIME_BITS=64 -D_FILE_OFFSET_BITS=64
#		--sysroot=/opt/arm-poky-linux-gnueabi/sysroots/cortexa5t2hf-neon-vfpv4-poky-linux-gnueabi
#
# CXX = arm-poky-linux-gnueabi-g++ -mthumb -mfpu=neon-vfpv4 -mfloat-abi=hard -mcpu=cortex-a5 -fstack-protector-strong -O2
#		-D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security -D_TIME_BITS=64 -D_FILE_OFFSET_BITS=64
#		--sysroot=/opt/arm-poky-linux-gnueabi/sysroots/cortexa5t2hf-neon-vfpv4-poky-linux-gnueabi
#
# Just for clarity and simplicity, for CFLAGS and CXXFLAGS, it will only be maintained those values that are completely related
# to SDK installation, and low level configuration. Additional flags will be set on Makefile.

CC = $(TARGET_PREFIX)gcc
CXX = $(TARGET_PREFIX)g++
# FIXME: Consider moving these lines into SDK Docker image, as specific project DO NOT have to know internal Docker image SDK installation paths
CFLAGS = -mthumb -mfpu=neon-vfpv4 -mfloat-abi=hard -mcpu=cortex-a5 -D_TIME_BITS=64 -D_FILE_OFFSET_BITS=64 --sysroot=/opt/arm-poky-linux-gnueabi/sysroots/cortexa5t2hf-neon-vfpv4-poky-linux-gnueabi
CXXFLAGS = -mthumb -mfpu=neon-vfpv4 -mfloat-abi=hard -mcpu=cortex-a5 -D_TIME_BITS=64 -D_FILE_OFFSET_BITS=64 --sysroot=/opt/arm-poky-linux-gnueabi/sysroots/cortexa5t2hf-neon-vfpv4-poky-linux-gnueabi
LDFLAGS =
LDLIBS =

