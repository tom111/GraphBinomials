// Library interface for graphbinomials cpp implementation
#include "monomial.h"
#include "binomial.h"

#include <vector>

namespace graphbinomial {

  bool inSameComponent (Monomial b1, Monomial b2, std::vector<Binomial> moves);
  
  // Just to test the cython interface
  void printMessage ();

};
