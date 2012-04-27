// Simple tests and usage examplex

#include <vector>
#include <iostream>
#include <typeinfo>

#include <assert.h>

#include "monomial.h"
#include "binomial.h"
#include "graphbinomial.h"

using namespace std;

void t1 () {
  // The simplest example: <x^2 - xy, xy - y^2>
  // TODO: Figure out smarter way to assing vectors
  int v1[2] = {2,0};
  int v2[2] = {1,1};
  int v3[2] = {0,2};
  vector<int> e1(v1, v1+2); 
  vector<int> e2(v2, v2+2); 
  vector<int> e3(v3, v3+3);

  Monomial m1(e1);
  Monomial m2(e2);
  Monomial m3(e3);

  Binomial b1(m1, m2);
  Binomial b2(m2, m3);
  vector<Binomial> edges;
  edges.push_back(b1);
  edges.push_back(b2);

  cout << "Testing connectivity of generating monomials" << endl;
  assert (inSameComponent (m1, m2, edges));
  assert (inSameComponent (m1, m3, edges));
  cout << "Passed." << endl;

  // test x and y:
  cout << "Testing non-connectivity of x,y"<< endl;
  vector<int> ex; ex.push_back(1); ex.push_back(0);
  vector<int> ey; ey.push_back(0); ey.push_back(1);
  Monomial x(ex);
  Monomial y(ey);
  assert (!inSameComponent(x,y, edges));
  cout << "Passed."<< endl;
}

int main(){
  t1();
  return 0;
}
