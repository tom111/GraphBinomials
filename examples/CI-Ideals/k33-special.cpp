// K33, codename "growing up"

#include <vector>
#include <iostream>

#include <assert.h>

#include "monomial.h"
#include "binomial.h"
#include "graphbinomial.h"
#include "fileIO.h"

using namespace std;

const int size=64;

// The input data
vector<Binomial> *edges = read4ti2File ("./k33.mar");

int main() {
  vector<Binomial>* quadrics = new vector<Binomial>; // CI moves
  vector<Binomial>* markov = new vector<Binomial>; // all other mvoes
  // sort them out
  for (unsigned int i = 0; i<edges->size(); i++){
    if ((*edges)[i].degree() == 2) { quadrics->push_back((*edges)[i]); }
    else { markov->push_back((*edges)[i]); } 
  }

  cout << "The proposed move has these two monomials: " << endl;
  cout << "Head: " << markov->at(8).head->toString() << endl;
  cout << "Tail: " << markov->at(8).tail->toString() << endl;
  
  // These two are not connected:
  Monomial m11("1 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 1 1 0 0 0 0 0 0 0 0 1 0 0");
  Monomial m21("1 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 1 0 0 1 0 0 0 0 0 0 1 0 0 0");
  assert(!inSameComponent (m11,m21, *quadrics));

  // But squaring the monomial coefficient makes them connected:
  Monomial m12("2 0 0 0 0 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 1 1 0 0 0 0 0 0 0 0 1 0 0");
  Monomial m22("2 0 0 0 0 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 1 0 0 1 0 0 0 0 0 0 1 0 0 0");
  assert(inSameComponent (m12, m22, *quadrics));

  // To prove the statement we are going to enumerate the components:
  cout << "Head and tail multiplied by a squarefree quadratic monomial:" << endl;
  cout << "Head: " << m11.toString() << endl;
  cout << "Tail: " << m21.toString() << endl;
  cout << "Connected components: " << endl;
  vector<Monomial*>* headComponent = enumerateComponent (m11, *quadrics);
  vector<Monomial*>* tailComponent = enumerateComponent (m21, *quadrics);
  cout << "Head: " << endl;
  for (unsigned int i = 0; i < headComponent->size(); i++) {
    cout << headComponent->at(i)->toString() << endl;
    delete headComponent->at(i);
  }
  cout << "Tail: " << endl;
  for (unsigned int i = 0; i < tailComponent->size(); i++) {
    cout << tailComponent->at(i)->toString() << endl;
    delete tailComponent->at(i);
  }
  delete headComponent;
  delete tailComponent;
  cout << "--------------------------" << endl;
  cout << "Multiplied with the square of the monomial, though:" << endl;
  cout << "Head: " << m12.toString() << endl;
  cout << "Tail: " << m22.toString() << endl;
  cout << "... they are in the same component: " << endl;
  headComponent = enumerateComponent (m12, *quadrics);
  for (unsigned int i = 0; i < headComponent->size(); i++) {
    cout << headComponent->at(i)->toString() << endl;
    delete headComponent->at(i);
  }
  cout << "qed." << endl;

  return 0;
}
