# Simple makefile to get started
CC=g++
CFLAGS=-c -Wall -fPIC
OPT=-O3
#LDFLAGS=
SOURCES=../monomial.cpp ../binomial.cpp ../graphbinomial.cpp ../fileIO.cpp
OBJECTS=$(SOURCES:.cpp=.o)

coco4: coco4.cpp $(SOURCES)
	$(CC) $(OPT) $(SOURCES) coco4.cpp -o coco4

coco-check: coco-check.cpp $(SOURCES)
	$(CC) $(OPT) $(SOURCES) coco-check.cpp -o coco-check

.cpp.o:
	$(CC) $(CFLAGS) $(OPT) $< -o $@

clean:
	rm -rf *.o *.so tests
