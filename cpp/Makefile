# Simple makefile to get started
CC=g++
CFLAGS=-c -Wall -fPIC
LDFLAGS=
SOURCES=monomial.cpp binomial.cpp graphbinomial.cpp
OBJECTS=$(SOURCES:.cpp=.o)
LIBRARY=graphbinomial.so

all: $(SOURCES) $(LIBRARY)

$(LIBRARY): $(OBJECTS)
	$(CC) $(LDFLAGS) -shared -fPIC $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o *.so
