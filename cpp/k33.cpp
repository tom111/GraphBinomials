// K33, codename "growing up"

#include <vector>
#include <iostream>

#include "monomial.h"
#include "binomial.h"
#include "graphbinomial.h"
#include "fileIO.h"

using namespace std;

const int size=64;

// The input data
vector<Binomial> *edges = read4ti2File ("/home/tom/GraphBinomials/cpp/k33.mar");

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
  return 0;
}
