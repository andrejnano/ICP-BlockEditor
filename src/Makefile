# ICP project - Block Editor

CXX = g++
CXXFLAGS = -O2 -std=c++14 -Wall

TARGET=blockeditor 			# name of program
FILES=$(wildcard *.cc) 	# all C++ source files


all: build

build: $(FILES)
	$(CXX) $(CXXFLAGS) $(FILES) -o $(TARGET)