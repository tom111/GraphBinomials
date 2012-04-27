// Simple tests and usage examplex

#include <vector>
#include <iostream>
#include <typeinfo>

#include "monomial.h"
#include "binomial.h"
#include "graphbinomial.h"

using namespace std;

int main(){
  // The simplest example: <x^2 - xy, xy - y^2>
  // TODO: Figure out smarter way to assing vectors
  const vector<int> e1; 
  const vector<int> e2; 
  const vector<int> e3;
  e1.push_back(2);
  e2.push_back(1);
  e3.push_back(0);
  e1.push_back(0);
  e2.push_back(1);
  e3.push_back(2);
  
  const Monomial m1(e1);
  const Monomial m2(e2);
  const Monomial m3(e3);

  Binomial b1(&m1, &m2);
  Binomial b2(&m2, &m3);
  vector<Binomial> edges;
  edges.push_back(b1);
  edges.push_back(b2);

  cout << inSameComponent (m1, m2, edges);
  cout << inSameComponent (m1, m3, edges);

  return 0;
}
