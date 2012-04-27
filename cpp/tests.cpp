// Simple tests and usage examplex

#include <vector>
#include <iostream>
#include <typeinfo>

#include "monomial.h"
#include "binomial.h"
#include "graphbinomial.h"

using namespace std;

void t1 () {
    // The simplest example: <x^2 - xy, xy - y^2>
  // TODO: Figure out smarter way to assing vectors
  vector<int> e1; 
  vector<int> e2; 
  vector<int> e3;
  e1.push_back(2);
  e2.push_back(1);
  e3.push_back(0);
  e1.push_back(0);
  e2.push_back(1);
  e3.push_back(2);
  
  Monomial m1(e1);
  Monomial m2(e2);
  Monomial m3(e3);

  Binomial b1(m1, m2);
  Binomial b2(m2, m3);
  vector<Binomial> edges;
  edges.push_back(b1);
  edges.push_back(b2);

  assert (!inSameComponent (m1, m2, edges));
  assert (!inSameComponent (m1, m3, edges));
}

int main(){
  t1();
  return 0;
}
