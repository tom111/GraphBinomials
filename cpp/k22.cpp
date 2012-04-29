// K22, handcrafted to serve as a testcase

#include <vector>
#include <iostream>

#include "monomial.h"
#include "binomial.h"
#include "graphbinomial.h"

using namespace std;

const int size=16;

int main () {
  // The quadrics
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

  // Do some easy checks:
  cout << inSameComponent (*m1.head, *m1.tail, edges) << endl;
  cout << inSameComponent (*m3.head, *m5.tail, edges) << endl;
  
  cout << inSameComponent (*m3.head, *m5.tail, edges) << endl;
  
  
  return 0;
}
