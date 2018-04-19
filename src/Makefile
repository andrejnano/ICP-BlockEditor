##
#	@file       Makefile
# @authors    Andrej Nano (xnanoa00), Stanislav Mechl (xmechl00)
# @date       2018-05-05
# @version    0.1
#
# @brief ICP 2018, Project - Block Editor. Makefile.
# 
# @section Description
#


# compiler
CXX = g++

# compiler flags
CXXFLAGS = -O2 -std=c++14 -Wall

# all C++ source files
FILES=$(wildcard *.cc)

# executable name
TARGET=blockeditor

all: build

build: $(FILES)
	$(CXX) $(CXXFLAGS) $(FILES) -o $(TARGET)