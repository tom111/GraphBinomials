# Simple makefile to get started
CC=g++
CFLAGS=-c -Wall -fPIC
OPT=-O3
#LDFLAGS=
SOURCES=coco-check.cpp
OBJECTS=$(SOURCES:.cpp=.o)

all: coco-check

coco-check: coco-check.o
	$(CXX) -lgraphbinomial -o coco-check coco-check.o

.cpp.o:
	$(CC) $(CFLAGS) $(OPT) $< -o $@

clean:
	rm -rf *.o *.so tests coco-check
