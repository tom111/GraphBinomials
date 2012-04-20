// Implementation of graphbinomials library

#include "graphbinomial.h"

#include <iostream>
#include <vector>

vector<Monomial*>* generateNeighbours (const vector<Monomial>& base, const vector<Binomial>& steps) {
  // This function calls functions which allocate memory for new monomials.
  vector<Monomial*>* result = new vector<Monomial*>;
  for (int i=0; i<steps.size(); i++){
    try {
      result->pushback(base.applyBinomialSafe(steps[i]));
    }
    catch (const char* e) {} // Move was not applicable
    // Try the other direction
    try {
      result->pushback(base.applyBinomialSafeReverse(steps[i]))
    }
    catch (const char* e) {}  // Move was not applicable
  };
  return result;
}

bool inSameComponent (const Monomial& m1, const Monomial& m2, const vector<Binomial>& moves) {
  // Use breadth first search on the graph.

  // Remember: Vectors are like good old C arrays.  Pointer arithmetic works!
  // Our vectors will store pointers
  
  // A vector to store the known monomials.
  // This will be cleaned up just before returning
  vector<Monomial*> knownMonomials;
  knownMonomials.push_back(new Monomial (m1));
  
  // Previously unseen monomials in the neighbourhood of the current layer
  // Those never need to be cleaned up, they also exist in knownMonomials
  vector<Monomial*> newMonomials;
  newMonomials.push_back(&m1); // Bootstrap neighbour generation with m1.

  while (newMonomials.size() > 0) {
    // The vector newNeigbours holds the neighbours of 'newMonomials' in each
    // step. Everything in newNeighbours is possessed by this while loop.
    vector<Monomial*>* newNeighbours = generateNeighbours (newMonomials, moves);
    // newMonomials is not needed anymore now.
    newMonomials.clear();
    for (int i=0; i<newNeighbours->size(); i++) {
      Monomial *n = (*newNeighbours)[i];
      if (n->isSame(m1)) {
	// We are done.  Clean up and return true
	// Delete the known monomials, we created all of those.
	for (int j=0; j<knownMonomials.size(); j++){ delete knownMonomials[j]; };
	// All the newNeighbours are still around: Clean them up
	for (int j=0; j<newNeighbours->size(); j++){ delete newNeighbours[j]; };
	return true;
      };
      if (!isPresent (knownMonomials, n)) {
	newMonomials.push_back(n);
	knownMonomials.push_back(n);
      }
      else {
	// n was already known to lie in the connected component:
	delete (*newNeighbours)[i];
	// Now 'n' is invalid, but that should not hurt since the for loop
	// moves on and will not touch it anymore.
      }
    }; // End of the for loop on newNeighbours
    // Need to free the vector itself
    delete newNeighbours;

    // Did we find new Monomials?  Generate informative output?
    if (newMonomials.size() > 0) {
      cout << "Next iteration will run with " << newMonomials.size() << " Neighbours" << endl;
    };
  }; // while loop on newMonomials

  // Did not find a connection.  Clean up and return.

  // The newMonomials are all either added to the knownMonomials or cleaned up
  // once we know they are duplicate.  Therefore we only need to clean up the
  // representation of the connected component.
  for (int j=0; j<knownMonomials.size(); j++) { delete knownMonomials[j]; };
  
  return false;
};

void printMessage (){
  std::cout << "Hallo Cython" << std::endl;
};
