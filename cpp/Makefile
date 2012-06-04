# Simple makefile, no install yet

ifndef CXX
  CCX=g++
endif 

cflags=${CFLAGS} -c -Wall -fPIC
opt=-O3
ldflags=${LDFLAGS} 
SOURCES=monomial.cpp binomial.cpp graphbinomial.cpp fileIO.cpp
OBJECTS=$(SOURCES:.cpp=.o)
LIBRARY=libgraphbinomial.so.0
SONAME=libgraphbinomial.so.0

all: $(SOURCES) $(LIBRARY) tests

tests:	tests.cpp $(SOURCES)
	$(CXX) -Wall -ggdb $(SOURCES) tests.cpp -o tests

debug: debug.cpp $(SOURCES)
	$(CC) $(SOURCES) debug.cpp -o debug

$(LIBRARY): $(OBJECTS)
	$(CXX) $(ldflags) -shared -Wl,-soname,$(SONAME) $(OBJECTS) -o $@

.cpp.o:
	$(CXX) $(cflags) $(opt) $< -o $@

clean:
	rm -rf *.o *.so tests
