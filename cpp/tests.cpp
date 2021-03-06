// Simple tests and usage examplex

#include <vector>
#include <iostream>
#include <typeinfo>

#include <assert.h>

#include "monomial.h"
#include "binomial.h"
#include "graphbinomial.h"
#include "orderIdeals.h"
#include "binomialCoefficients.h"
#include "Permutations.h"
#include "tool.h"

using namespace std;

void t1 () {
  // The simplest example: <x^2 - xy, xy - y^2>
  Monomial m1("2 0");
  Monomial m2("1 1");
  Monomial m3("0 2");

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
  Monomial mp1("0 0 0 1 1 2 1 1 6 3 1 2 0 0 1 1");
  Monomial mp2("1 0 0 0 0 0 1 2 1 1 1 2 3 1 6 1"); 
  // Should be same degree.
  
  Monomial *t1 = mp1.multiply(*m1.head);
  Monomial *t2 = mp2.multiply(*m2.tail);
  assert (! inSameComponent (*t1, *t2, edges));
}

void t3(){
  Monomial m1("3 0");
  Monomial m2("2 1");
  Monomial m3("1 2");
  Monomial m4("0 3");
  Binomial b1(m1, m2);
  Binomial b2(m2, m3);
  Binomial b3(m3, m4);
  vector<Binomial> edges;
  edges.push_back(b1);
  edges.push_back(b2);
  edges.push_back(b3);
  vector<Monomial*> *component = enumerateComponent(Monomial("3 3"), edges);
  cout << "The following should be the list of monomials of degree 6:" << endl;
  for (unsigned int i = 0; i< component->size(); i++) {
    cout << component->at(i)->toString() << endl;
  }
  assert (component->size() == 7);
}

void t4(){
  // K22 Example
  // Checking connected components.
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

  Monomial mp1("0 0 0 1 1 2 1 1 6 3 1 2 0 0 1 1");
  vector<Monomial*>* c1 = enumerateComponent(mp1, edges);
  vector<Monomial*>* c2 = enumerateComponent(*c1->at(c1->size()-2), edges);
  vector<Monomial*>* c3 = enumerateComponent(*c1->at(c1->size()-3), edges);
  vector<Monomial*>* c4 = enumerateComponent(*c1->at(c1->size()-22), edges);

  assert (sameList (*c1,*c2));
  assert (sameList (*c2,*c3));
  assert (sameList (*c3,*c4));
  assert (sameList (*c4,*c1));
}

void t5(){
  Monomial m1("3 2 1");
  vector<Monomial*> *below = m1.listBelow();
  vector<Monomial*> *below2 = listBelow(*below);
  cout << "-----start--------" << endl;
  for (unsigned int i=0; i<below->size(); i++){
    cout << below->at(i)->toString() << endl;
  }
  cout << "-----next--------" << endl;
  for (unsigned int i=0; i<below2->size(); i++){
    cout << below2->at(i)->toString() << endl;
  }
  cout << endl;
}

void t6(){
  Monomial m1("0 2 1");
  Monomial m2("0 3 0");
  Monomial m3("0 0 3");  vector<Monomial*> *start = new vector<Monomial*>;
  start->push_back(&m1);
  start->push_back(&m2);
  start->push_back(&m3);
  vector<int> h = hVector(*start);
  cout << "-----hVector--------" << endl;
  for (unsigned int i=0; i<h.size(); i++){
    cout << h.at(i) << " ";
  }
  cout << endl;
  assert (h == stringToVector ("1 2 3 3"));
}

void t6_2() {
  Monomial m2("3 8 7 6 9");
  Monomial m3("3 7 8 9 6");  
  Monomial m4("9 3 8 7 6");
  Monomial m5("8 7 3 6 9");

  vector<Monomial*> *start = new vector<Monomial*>;
  start->push_back(&m2);
  start->push_back(&m3);
  start->push_back(&m4);
  start->push_back(&m5);

  cout << endl;
  cout << "Computing a larger h-vector:" << endl;
  vector<int> h = hVector(*start);
  for (unsigned int i=0; i<h.size(); i++){
    cout << h.at(i) << " ";
  }
  cout << endl;
  cout.flush();
  assert (h == stringToVector ("1 5 15 35 70 126 210 330 495 713 988 1320 1702 2120 2554 2974 3342 3620 3774 3784 3647 3373 2987 2526 2033 1552 1120 759 478 275 140 60 20 4"));
}

void t7(){
  cout << "Monomials of degree 2 in 4 variables: " << endl;
  vector<Monomial*> *mons = allMonomials(2, 4);
  for (unsigned int i=0; i<mons->size(); i++){
    cout << mons->at(i)->toString() << endl;
  }
  assert(binomialCoefficient(100,5)==75287520);
  assert(binomialCoefficient(104,5)==91962520);
  assert(binomialCoefficient(136,7)==145944307080);
}

void t8 (){
  int d = 4;
  int t = 4;
  int n = 4;
  vector<int> *h = new vector<int>;
  h->push_back(1);
  h->push_back(3);
  h->push_back(5);
  h->push_back(5);
  h->push_back(4);
  // enumeratePureOSequences (d, t, n, h);  // This will break execution of tests
  enumeratePureOSequences (d, t, n);
}

void t9() {
  Permutations P(4);
  cout << "Permutations on four elements:" << endl;
  do {
    P.display();
  } while (P.next());
  cout << endl;
}

void t10(){
  vector<int> a = stringToVector ("5 4 3 2 1");
  vector< vector<int> > res = testAlexRecipe (a, 3, 4);
  assert (isPureOSequenceAlexRecipe (a,3,4,res[res.size()-2], 0));
  // For this to work we need to permute a
  assert (isPureOSequenceAlexRecipe (a,3,4,stringToVector("1 3 6 10 15 20 24 27 27 24 18 11 4"), 1));
}

void t11(){
  // assert (isAdmissableCombination (stringToVector("1 2 3 4 10 11 12 13 14"), stringToVector("7 10 12")));
  // assert (!isAdmissableCombination (stringToVector("10 11 12 13 14"), stringToVector("7 10 12")));
}

void t12(){
  vector<int> h = stringToVector("1 3 6 10 15 20 24 27 27 24 18 11 4");
  printIntVector (differenceVector (h));
}

int main(){
  t1();
  t2();
  t3();
  t4();
  t5();
  t6(); // approximately seven seconds
  t6_2(); // long ...
  t7();
  t8();
  t9();
  t10();
  t11();
  t12();
  return 0;
}
