// Implementation of orderIdeals library

#include <iostream>
#include <vector>

#include <assert.h>

#include "graphbinomial.h"

using namespace std;

vector<Monomial*>* listBelow (const vector<Monomial*>& mons) {
  // list all monomials directly below a list of given monomials
  vector<Monomial*>* res = new vector<Monomial*>;
  vector<Monomial*> *belowCurrent;
  for (unsigned int i=0; i<mons.size(); i++){
    belowCurrent = mons.at(i)->listBelow();
    for (unsigned int j=0; j<belowCurrent->size(); j++){
      // Check if that monomial is already known...
      if (! isPresent (*res, *belowCurrent->at(j))) {
	// add it
	res->push_back (new Monomial (*belowCurrent->at(j)));
      }
      delete belowCurrent->at(j);
    }
    // The following does not call destructors because pointers are saved.
    delete belowCurrent;
  }
  return res;
}

vector<int> hVector (const vector<Monomial*>& mons){
  // Compute hVector of an order ideal given by a list of monomial generators
  // For now we assume that all monomials are of a fixed degree
  vector<int> result; // will be inverted before returning
  int d = mons.at(0)->degree(); // socle degree should be fixed
  cout << "socle degree: " << d << endl;
  for (unsigned int i =0; i<mons.size(); i++){
    assert (d == mons.at(i)->degree());
  }
  result.push_back(mons.size());// CM-type
  cout << "CM-type: " << mons.size() << endl;
  vector<Monomial*> *current = listBelow(mons);
  vector<Monomial*> *next;
  while (current->size()>0) {
    cout << "Current round of monomials" << endl;
    for (unsigned int kk=0; kk<current->size(); kk++){
      cout << current->at(kk)->toString() << endl;
    }
    cout << "---" << endl;
    result.push_back(current->size());
    next = listBelow(*current);
    delete current;
    current = next;
  }
  vector<int> realresult;
  unsigned int s = result.size();
  for (unsigned int i=0; i<s; i++){
    realresult.push_back(result.at(s-i-1));
  }
  return realresult;
}
