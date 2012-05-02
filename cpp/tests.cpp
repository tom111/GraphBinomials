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
  vector<int> e3(v3, v3+2);

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

void t2 () {
  // K22 Example
  Binomial b1("-1 0 1 0 0 0 0 0 1 0 -1 0 0 0 0 0");
  Binomial b2("0 -1 0 1 0 0 0 0 0 1 0 -1 0 0 0 0");
  Binomial b3("0 0 0 0 -1 0 1 0 0 0 0 0 1 0 -1 0");
  Binomial b4("0 0 0 0 0 -1 0 1 0 0 0 0 0 1 0 -1");
  Binomial b5("-1 1 0 0 1 -1 0 0 0 0 0 0 0 0 0 0");
  Binomial b6("0 0 -1 1 0 0 1 -1 0 0 0 0 0 0 0 0");
  Binomial b7("0 0 0 0 0 0 0 0 -1 1 0 0 1 -1 0 0");
  Binomial b8("0 0 0 0 0 0 0 0 0 0 -1 1 0 0 1 -1");
  
  vector<Binomial> edges;
  edges.push_back(b1); edges.push_back(b2); edges.push_back(b3);
  edges.push_back(b4); edges.push_back(b5); edges.push_back(b6);
  edges.push_back(b7); edges.push_back(b8);

  // The quartics
  Binomial m1 ("0 0 0 0 1 -1 -1 1 -1 1 1 -1 0 0 0 0");
  Binomial m2 ("0 0 1 -1 -1 1 0 0 0 0 -1 1 1 -1 0 0");
  Binomial m3 ("0 1 -1 0 0 -1 1 0 0 -1 1 0 0 1 -1 0");
  Binomial m4 ("0 1 0 -1 0 -1 0 1 -1 0 1 0 1 0 -1 0");
  Binomial m5 ("1 -1 -1 1 0 0 0 0 0 0 0 0 -1 1 1 -1");
  Binomial m6 ("1 -1 0 0 0 0 -1 1 -1 1 0 0 0 0 1 -1");
  Binomial m7 ("1 0 -1 0 -1 0 1 0 0 -1 0 1 0 1 0 -1");
  Binomial m8 ("1 0 0 -1 -1 0 0 1 -1 0 0 1 1 0 0 -1");

  // Do some easy checks (no move applies at all)
  cout << inSameComponent (*m1.head, *m1.tail, edges) << endl;
  
  // Choose some high multipliers
  Monomial mp1("1 1 1 1 1 2 1 1 6 3 1 2 1 1 1 1");
  Monomial mp2("1 1 1 1 1 1 1 2 1 1 1 2 3 1 6 1"); 
  // Should be same degree.
  
  Monomial *t1 = mp1.multiply(*m1.head);
  Monomial *t2 = mp2.multiply(*m2.tail);
  assert (! inSameComponent (*t1, *t2, edges));
}

int main(){
  t1();
  t2();
  return 0;
}
