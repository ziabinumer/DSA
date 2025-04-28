CXX = g++
CXXFLAGS = -std=c++11 -Wall

TARGET = build/Task1

SRCS = main.cpp AVL.cpp BST.cpp Course.h

all: prepare $(TARGET)

prepare:
	mkdir -p build

$(TARGET):
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -rf build
