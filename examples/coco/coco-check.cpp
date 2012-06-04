// Coco reality check
// all moves to be checked are differences of basic moves

#include <vector>
#include <iostream>

#include <assert.h>

#include "graphbinomials/monomial.h"
#include "graphbinomials/binomial.h"
#include "graphbinomials/graphbinomial.h"
#include "graphbinomials/fileIO.h"

using namespace std;

// const int size=135;

// The input data
vector<Binomial> *edges = read4ti2File ("./coco-moves");
vector<Binomial> *toCheck = read4ti2File ("./lattice-differences");

int main() {
  cout << "There are " << edges->size() << " moves and " 
       << toCheck->size() << " checks." << endl;

  Monomial *m1;
  Monomial *m2;
  // Check for connectedness of each toCheckMove
  for (unsigned int i=0; i < toCheck->size(); i++){
    m1 = toCheck->at(i).head;
    m2 = toCheck->at(i).tail;
    cout << m1->degree() << endl;
    vector<Monomial*>* component = enumerateComponent(*m1, *edges);
    for (unsigned int j=0; j<component->size(); j++){
      cout << component->at(j)->toString() << endl;
    }
    // assert(inSameComponent (*m1, *m2, *edges));
  };
  return 0;
}
