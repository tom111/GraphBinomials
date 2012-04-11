// Implementation of graphbinomials library

#include "graphbinomial.h"

#include <iostream>
#include <vector>

vector<Monomial*> generateNeighbours (const vector<Monomial>& base, const vector<Binomial>& steps) {
  // Warning: allocates memory for the individual monomials
  // TODO: Implement me
}

bool inSameComponent (const Monomial& m1, const Monomial& m2, const vector<Binomial>& moves) {
  // Use breadth first search on the graph.

  // Remember: Vectors are like good old C arrays.  They store pointers!
  
  // A vector to store the known monomials
  vector<Monomial*> knownMonomials;
  knownMonomials.push_back(new Monomial (m1));
  
  // Previously unseen monomials in the neighbourhood of the current layer
  // Those never need to be cleaned up, they also exist in knownMonomials
  vector<Monomial*> newMonomials;
  newMonomials.push_back(&m1); // Bootstrap the neighbour generation.  m1 will
			       // not be deleted.

  // This will hold new neighbours in each step
  while (newMonomials.size() > 0) {
    vector<Monomial*> newNeighbours = generateNeighbours (newMonomials, moves);
    // Everything in newNeighbours is possessed by this function.  Next we
    // clean the vector newMonomials.  For this we don't need to free anything
    // since its content is either external (in the first round) or duplicate
    // (with 'knownMonomials' in all other rounds.)
    newMonomials.clear();
    for (int i=0; i<newNeighbours.size(); i++) {
      Monomial *n = newNeighbours[i];
      if (n->isSame(m1)) {
	// We are done.  Clean up and return true
	// Delete the known monomials, we created all of those.
	for (int j=0; j<knownMonomials.size(); j++){
	  delete knownMonomials[j]
	}
	// All the newNeighbours are still around: Clean them up
	for (int j=0; j<newNeighbours.size(); j++){
	  delete newNeighbours[j]
	}
	// This should be all
	return true;
      };
      if (!isPresent (knownMonomials, n)) {
	newMonomials.push_back(n);
	knownMonomials.push_back(n);
      }
      else {
	// we already had n, get rid of it
	delete newNeighbours[i];
	// Now 'n' is invalid, but that should not hurt since the for loop
	// moves on now.
      }
    }; // End of the for loop on newNeighbours

    // Did we find new Monomials?  Generate informative output?
    if (newMonomials.size() > 0) {
      cout << "Next iteration will run with " << newMonomials.size() << " Neighbours" << endl;
    };
  }; // while loop on newMonomials

  // Did not find a connection.  Clean up and go home
  
  return false;
};

void printMessage (){
  std::cout << "Hallo Cython" << std::endl;
};


