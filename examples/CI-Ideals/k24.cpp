// K33, codename "growing up"

#include <vector>
#include <iostream>

#include "graphbinomials/monomial.h"
#include "graphbinomials/binomial.h"
#include "graphbinomials/graphbinomial.h"
#include "graphbinomials/fileIO.h"

using namespace std;

const int size=64;

// The input data
vector<Binomial> *edges = read4ti2File ("./k24.mar");

// Use trick to read in all integer vectors of size two:
// vector<Binomial> *varproducts = read4ti2File ("/home/tom/GraphBinomials/cpp/var2.mar");

// Squarefree:
vector<Binomial> *varproducts = read4ti2File ("./var2squarefree.mar");


// K24 is prime, therefore one should never reach the jackpot situation We
// remove the break and there test every squarefree monomial which does not
// make a move connected, whether the square makes it connected.  Note that
// this is not a sufficient test for radicality of course.

int main() {
  vector<Binomial>* quadrics = new vector<Binomial>; // CI moves
  vector<Binomial>* markov = new vector<Binomial>; // all other mvoes
  // sort them out
  for (unsigned int i = 0; i<edges->size(); i++){
    if ((*edges)[i].degree() == 2) { quadrics->push_back((*edges)[i]); }
    else { markov->push_back((*edges)[i]); } 
  }
  cout << "There are " << quadrics->size() << " quadrics and " 
       << markov->size() << " other moves." << endl;

  // Prepare products of variables
  vector<Monomial> *var2 = new vector<Monomial>;
  for (unsigned int i=0; i < varproducts->size(); i++){
    var2->push_back(*varproducts->at(i).head);
  }
  delete varproducts;

  Monomial *m1;
  Monomial *m2;
  // Examine each higher markov move and try to find a squarefree
  // witness.
  for (unsigned int i=0; i<markov->size(); i++){
    // Check all variables
    // Todo (if necessary)

    // Check all pairs of variables.
    for (unsigned int j=0; j < var2->size(); j++){
      m1 = markov->at(i).head->multiply(var2->at(j));
      m2 = markov->at(i).tail->multiply(var2->at(j));
      if (! inSameComponent (*m1, *m2, *quadrics) ) {
	// try the square 
	Monomial *m3 = m1->multiply(var2->at(j));
	Monomial *m4 = m2->multiply(var2->at(j));
	if (inSameComponent (*m3, *m4, *quadrics) ) {
	  // Jackpot !
	  cout << "Jackpot!" << endl;
	  cout << "Connected monomials: " << m3->toString() << " --- " << m4->toString() << endl;
	  return 0;
	}
	delete m3;
	delete m4;
      };
      // No else path for this pseudo-radicality check
      delete m1;
      delete m2;
    };
    cout << i << " of " << markov->size() << "done." << endl;
  };
  return 0;
}
