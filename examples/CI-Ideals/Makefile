# Simple makefile to get started
CXX=g++
CFLAGS=-c -Wall -fPIC
SOURCES=k22.cpp k23.cpp k24.cpp k33.cpp k33-special.cpp g154.cpp
OBJECTS=$(SOURCES:.cpp=.o)
PROGRAMS=$(SOURCES:.cpp=)
OPT=-O3
LDFLAGS=

all: $(SOURCES) $(OBJECTS) $(PROGRAMS)

k22: k22.o
	$(CXX) -lgraphbinomial -o k22 k22.o

k23: k23.o
	$(CXX) -lgraphbinomial -o k23 k23.o

k24: k24.o
	$(CXX) -lgraphbinomial -o k24 k24.o

k33: k33.o
	$(CXX) -lgraphbinomial -o k33 k33.o

k33-special: k33-special.o
	$(CXX) -lgraphbinomial -o k33-special k33-special.o

g154: g154.o
	$(CXX) -lgraphbinomial -o g154 g154.o

.cpp.o:
	$(CXX) $(CFLAGS) $(OPT) $< -o $@

clean:
	rm -rf *.o *.so $(PROGRAMS)