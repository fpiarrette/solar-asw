
CC = gcc
CXX = g++
CFLAGS =
CXXFLAGS = -std=c++14
LDFLAGS =
LDLIBS = -lstdc++

# Include specific tests for host platform, tipically they that do not depend on hardware or devices
tests: test_rest
