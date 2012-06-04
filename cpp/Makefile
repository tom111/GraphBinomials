# Simple makefile, no install yet
CC=g++
CFLAGS=-c -Wall -fPIC
OPT=-O3
LDFLAGS=
SOURCES=monomial.cpp binomial.cpp graphbinomial.cpp fileIO.cpp
OBJECTS=$(SOURCES:.cpp=.o)
LIBRARY=libgraphbinomial.so.1

all: $(SOURCES) $(LIBRARY) tests

tests:	tests.cpp $(SOURCES)
	$(CC) -Wall -ggdb $(SOURCES) tests.cpp -o tests

debug: debug.cpp $(SOURCES)
	$(CC) $(SOURCES) debug.cpp -o debug

$(LIBRARY): $(OBJECTS)
	$(CC) $(LDFLAGS) -shared -Wl,-soname,libgraphbinomial.so.1 $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(OPT) $< -o $@

clean:
	rm -rf *.o *.so tests
