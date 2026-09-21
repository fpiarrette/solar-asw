
CC = gcc
CXX = g++
CFLAGS =
CXXFLAGS =
LDFLAGS =
LDLIBS =

# Include specific tests for host platform, tipically they that do not depend on hardware or devices
tests: test_rest
