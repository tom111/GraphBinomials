# Simple makefile to get started
CC=g++
CFLAGS=-c -Wall -fPIC
LDFLAGS=
SOURCES=monomial.cpp binomial.cpp graphbinomial.cpp fileIO.cpp
OBJECTS=$(SOURCES:.cpp=.o)
LIBRARY=libgraphbinomial.so.1

all: $(SOURCES) $(LIBRARY) tests

tests:	tests.cpp $(SOURCES)
	$(CC) -Wall -ggdb $(SOURCES) tests.cpp -o tests

k22: k22.cpp $(SOURCES)
	$(CC) $(SOURCES) k22.cpp -o k22

k33: k33.cpp $(SOURCES)
	$(CC) $(SOURCES) k33.cpp -o k33

$(LIBRARY): $(OBJECTS)
	$(CC) $(LDFLAGS) -shared -Wl,-soname,libgraphbinomial.so.1 $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o *.so tests