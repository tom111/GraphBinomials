// Implementation of graphbinomials library

#include "graphbinomial.h"

#include <iostream>
#include <vector>

// TODO: Fix this double definition (and use an iterator with std::find)!
bool isPresent (const vector<Monomial>& list, const Monomial& element){
  for (unsigned int i=0; i<list.size(); i++){
    if (element==(list[i])) {
      return true;
    };
  };
  return false;
};

bool isPresent (const vector<Monomial*>& list, const Monomial& element){
  for (unsigned int i=0; i<list.size(); i++){
    if (element==(*list[i])) {
      return true;
    };
  };
  return false;
};

vector<Monomial*>* generateNeighbours (const vector<Monomial>& base, const vector<Binomial>& steps) {
  // This function calls functions which allocate memory for new
  // monomials. and also allocates its result vector.  The main loop is
  // responsible for clean-up.
  vector<Monomial*>* result = new vector<Monomial*>;
  Monomial* myMonomial; // Will save intermediate references
  for (unsigned int j=0; j<base.size(); j++){
    for (unsigned int i=0; i<steps.size(); i++){
      try {
	myMonomial = base[j].applyBinomialSafe(steps[i]);
	if (isPresent(*result, *myMonomial)) {
	  delete myMonomial;
	  break;
	}
	else {
	  result->push_back(myMonomial);
	};
      }
      catch (const char* e) {}; // Move was not applicable
      // Try the other direction
      try {
	myMonomial = base[j].applyBinomialSafeReverse(steps[i]);
	if (isPresent (*result, *myMonomial)) {
	  delete myMonomial;
	  break;
	} 
	else {
	  result->push_back(myMonomial);
	};
      }
      catch (const char* e) {}; // Move was not applicable
    };
  };
  return result;
};

bool inSameComponent (const Monomial& m1, const Monomial& m2, const vector<Binomial>& moves) {
  // Use breadth first search on the graph.

//   // Verbose debugging output 
//   cout << "Starting inSameComponent with the following data:" << endl;
//   cout << "Monomial 1: " << m1.toString() << endl;
//   cout << "Monomial 2: " << m2.toString() << endl;
//   cout << "I got " << moves.size() << " edges to use: " << endl;
// 
//   for (unsigned int i=0; i<moves.size(); i++){
//     cout << "   " << moves[i].toString() << endl;
//   }

  // Remember: Vectors are like good old C arrays.  Pointer arithmetic works!
  // Our vectors will store pointers
  
  // A vector to store the known monomials.
  // This will be cleaned up just before returning
  vector<Monomial*> knownMonomials;
  knownMonomials.push_back(new Monomial (m1));
  
  // Previously unseen monomials in the neighbourhood of the current layer
  // Those never need to be cleaned up, they also exist in knownMonomials
  vector<Monomial> newMonomials;
  newMonomials.push_back(m1); // Bootstrap neighbour generation with m1.

  vector<Monomial*>* newNeighbours;
  while (newMonomials.size() > 0) {
    // The vector newNeigbours holds the neighbours of 'newMonomials' in each
    // step. Everything in newNeighbours is possessed by this while loop.
    newNeighbours = generateNeighbours (newMonomials, moves);
//     // Verbose debugging output:
//     cout << "Done Computing Neighbours: Here they are:" << endl;
//     for (unsigned int ii = 0; ii < newNeighbours->size(); ii++){
//       cout << ii << ": " << newNeighbours->at(ii)->toString() << endl;
//     }
//     cout << " ------- makes sense ? -------- " << endl;
    // newMonomials is not needed anymore now.
    newMonomials.clear();
    for (unsigned int i=0; i<newNeighbours->size(); i++) {
      Monomial *n = (*newNeighbours)[i];
      if (*n==m2) {
// 	// Verbose debugging output:
// 	cout << "I just concluded that the following monomials are the same: " << endl;
// 	cout << " 1: " << n->toString() << endl;
// 	cout << " 2: " << m2.toString() << endl;
	
	// We are done searching.  Clean up and return true
	// Delete the known monomials, we created all of those.
	for (unsigned int j=0; j<knownMonomials.size(); j++){ delete knownMonomials[j]; };
	// Clean newneighbours (will call desctructors of the content too)
	delete newNeighbours;
	return true;
      };
      if (!isPresent(knownMonomials, *n)) {
	newMonomials.push_back(*n);
	knownMonomials.push_back(n);
      }
      else {
	// n was already known to lie in the connected component:
	delete (*newNeighbours)[i];
	// Now 'n' is invalid, but that should not hurt since the for loop
	// moves on and will not touch it anymore.
      }
    }; // End of the for loop on newNeighbours
    // Need to free newNeighbours.
    delete newNeighbours;

    // Did we find new Monomials?  Generate informative output?
    // if (newMonomials.size() > 0) {
    //  cout << "Next iteration will run with " << newMonomials.size() << " Neighbours" << endl;
    // };
  }; // while loop on newMonomials

  // Did not find a connection.  Clean up and return.

  // The newMonomials are all either added to the knownMonomials or cleaned up
  // once we know they are duplicate.  Therefore we only need to clean up the
  // representation of the connected component.
  for (unsigned int j=0; j<knownMonomials.size(); j++) { delete knownMonomials[j]; };
  
  return false;
};

vector<Monomial*>* enumerateComponent (const Monomial& m, const vector<Binomial>& moves) {
  // similar to inSameComponent, see comments there.
  vector<Monomial*> *knownMonomials = new vector<Monomial*>;
  knownMonomials->push_back(new Monomial (m));
  
  vector<Monomial> newMonomials;
  newMonomials.push_back(m); // Bootstrap neighbour generation with m.

  vector<Monomial*>* newNeighbours;
  Monomial *n;
  while (newMonomials.size() > 0) {
    newNeighbours = generateNeighbours (newMonomials, moves);
    newMonomials.clear();
    for (unsigned int i=0; i<newNeighbours->size(); i++) {
      n = newNeighbours->at(i);
      // Remove stuff that we already know
      if (!isPresent(*knownMonomials, *n)) {
	newMonomials.push_back(*n);
	knownMonomials->push_back(n);
      }
      else {
	delete n;
	// Now 'n' is invalid, but that should not hurt since the for loop
	// moves on and will not touch it anymore.
      }
    }; // End of the for loop on newNeighbours
    // Need to free newNeighbours vector that generateNeighbours allocated
    delete newNeighbours;
  }; // while loop on newMonomials
  // done, return the component
  return knownMonomials;
};


