# Simple makefile, no install yet

ifndef CXX
  CCX=g++
endif 

cflags=${CFLAGS} -c -Wall -fPIC
opt=-O3
ldflags=${LDFLAGS} 
SOURCES=monomial.cpp binomial.cpp graphbinomial.cpp fileIO.cpp orderIdeals.cpp
HEADERS=$(SOURCES:.cpp=.h) tool.h binomialCoefficients.h Combinations.h Permutations.h
OBJECTS=$(SOURCES:.cpp=.o)
LIBRARY=libgraphbinomial.so.0
SONAME=libgraphbinomial.so.0

all: $(HEADERS) $(SOURCES) $(LIBRARY) tests

tests:	tests.cpp $(SOURCES) $(HEADERS)
	$(CXX) -Wall -ggdb $(SOURCES) tests.cpp -o tests

alex:	alex.cpp $(SOURCES) $(HEADERS)
	$(CXX) -Wall -O3 $(SOURCES) alex.cpp -o alex

matteo:	matteo.cpp $(SOURCES) $(HEADERS)
	$(CXX) -Wall -O3 $(SOURCES) matteo.cpp -o matteo

tom:	tom.cpp $(SOURCES) $(HEADERS)
	$(CXX) -Wall -O3 $(SOURCES) tom.cpp -o tom

play:	play.cpp $(SOURCES) $(HEADERS)
	$(CXX) -Wall -O3 $(SOURCES) play.cpp -o play

debug: debug.cpp $(SOURCES) $(HEADERS)
	$(CC) $(SOURCES) debug.cpp -o debug

$(LIBRARY): $(OBJECTS) $(HEADERS)
	$(CXX) $(ldflags) -shared -Wl,-soname,$(SONAME) $(OBJECTS) -o $@

.cpp.o:
	$(CXX) $(cflags) $(opt) $< -o $@

clean:
	rm -rf *.o *.so tests alex matteo play
