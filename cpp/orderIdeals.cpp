// Implementation of orderIdeals library

#include <cstdlib>
#include <iostream>
#include <vector>

#include <assert.h>

#include "orderIdeals.h"
#include "graphbinomial.h"
#include "Combinations.h"
#include "Permutations.h"
#include "tool.h"
#include "binomialCoefficients.h"

using namespace std;

vector<Monomial*>* allMonomials (const int degree, const int numvars) {
  // Lists all monomials of a given digree in given number of
  // variables.

  // Algorithm: Putting N things into M boxes is equivalent to
  // arranging M-1 boxes and the N things into a sequence and then
  // putting every object into the box right of it.  Therefore we
  // generate all combinations of M-1 things from N-M-1 things (think
  // of the positions of the boxes), and then take consecutive
  // differences to turn those into monomials.
  int N = numvars-1+degree;
  int M = numvars-1;
  int sum = 0;
  Combinations C(M,N);
  vector<int> v(numvars,0);  // length numvars, entries zero
  vector<Monomial*> *result = new vector<Monomial*>;
  do {
    // C.display();
    v[0] = C(0);
    sum = v[0];
    for (int i = 1; i < M; i++){
      v[i] = C(i)-C(i-1)-1;
      sum += v[i];
    }
    v[numvars-1] = degree-sum;
    result->push_back(new Monomial(v));
  } while(C.next());
  return result;
}

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
	res->push_back (belowCurrent->at(j));
      }
      else {
	delete belowCurrent->at(j);
      }
    }
    // The following does not call destructors because pointers are saved.
    delete belowCurrent;
  }
  return res;
}

vector<Monomial*>* listBelowPure (const vector<Monomial*>& mons) {
  // list all monomials directly below a list of given monomials, all
  // in the same degree
  int d = mons.at(0)->degree(); // socle degree should be constant
  if (d == 0) return new vector<Monomial*>;
  // cout << "socle degree: " << d << endl;
  for (unsigned int i =0; i<mons.size(); i++){
    assert (d == mons.at(i)->degree());
  }
  vector<Monomial*>* res = new vector<Monomial*>;
  vector<Monomial*> *candidates = allMonomials(d-1, mons.at(0)->length);
  for (unsigned int i=0; i < candidates->size(); i++){
    for (unsigned int j=0; j < mons.size(); j++){
      if (mons.at(j)->isDivisible(*candidates->at(i))) {
	res->push_back(new Monomial (*candidates->at(i)));
	break; // move on to the next candidate
      }
    }
    delete candidates->at(i);
  }
  delete candidates;
  return res;
}

vector<int> hVector (const vector<Monomial*>& mons){
  // Compute hVector of an order ideal given by a list of monomial generators
  // For now we assume that all monomials are of a fixed degree
  vector<int> result; // will be inverted before returning
  int d = mons.at(0)->degree(); // socle degree should be fixed
  long n = mons.at(0)->length;
  // cout << "socle degree: " << d << endl; cout.flush();
  for (unsigned int i =0; i<mons.size(); i++){
    assert (d == mons.at(i)->degree());
  }
  result.push_back(mons.size());// CM-type
  // cout << "CM-type: " << mons.size() << endl;

  // Heuristics: If the number of monomials in the next level is much
  // larger than the expected number of monomials in the algebra, then
  // use the descend algorithm, otherwise the list-all algorithm

  vector<Monomial*> *current = listBelow(mons);
  vector<Monomial*> *next;
  unsigned long long numberOfMonomials;
  while (current->size()>0) {
    // cout << "now at degree : " << d-- << endl;
    d--;
    numberOfMonomials = binomialCoefficient(n-1+d-1,n-1); // in the layer _below_
    // cout << "Current round of monomials" << endl;
    // for (unsigned int kk=0; kk<current->size(); kk++){
    //      cout << current->at(kk)->toString() << endl;
    // }
    // cout << "---" << endl;
    result.push_back(current->size());
    // Apply the heuristics:
    if (current->size() > numberOfMonomials) { 
      // cout << "chose Pure ";
      next = listBelowPure (*current);
    }
    else  {
      // cout << "chose standard ";
      next = listBelow(*current);
    }
    deleteVector (current);
    current = next;
    // cut-off if all monomials are exhausted:
    if (next->size() == numberOfMonomials){
      // cout << "CutOff reached";
      for (int i = d-1; i >= 0; i--){
	result.push_back (binomialCoefficient(n-1+i,n-1));
      }
      deleteVector(next);
      break;
    }
  }
  vector<int> realresult;
  unsigned int s = result.size();
  for (unsigned int i=0; i<s; i++){
    realresult.push_back(result.at(s-i-1));
  }
  return realresult;
}

vector< vector<int> > enumeratePureOSequences (const int degree, const int type, const int numvars){
  // Need all combinations of type many monomials in numvars variables
  // of given degree
  vector<Monomial*> *allMons = allMonomials(degree, numvars);
  Combinations C(type, allMons->size());
  vector<Monomial*> *currentSocle;
  vector< vector<int> > result;
  unsigned long long todo = binomialCoefficient(allMons->size(),type);
  long counter = 0;
  do {
    // Informative output ?
    if (counter++ % 100000 == 0){
      cout << "Checking socle number " << counter << " out of " << todo << endl;
    }
    currentSocle = new vector<Monomial*>;
    for (int i=0; i<type; i++){
      currentSocle->push_back (allMons->at(C(i)));
    }
    // A shortcut to mod out some symmetry: We will skip every loop in
    // which the first monomial of the socle has an exponent vector
    // that is not weakly decreasing.
    if (!isWeaklyIncreasing ((*currentSocle)[0]->exponents)) { 
      delete currentSocle;
      continue;
    }
    vector<int> h = hVector(*currentSocle);
    if (! isPresent (result, h)){
      result.push_back(h);
      cout << "Current number of different pure O sequences : " << result.size() << endl;
      // A useful count for leak detection:
      // cout << "Current number of monomials around: " << Monomial::n << endl;
    }
    // Just delete the socle data structure, it's content is preserved
    // since it also lives in allMons
    delete currentSocle;
    } while (C.next());

  cout << "Result: " << endl;
  for (unsigned int i = 0; i <  result.size(); i++){
    for (unsigned int j = 0; j <  result.at(i).size(); j++){
      cout << result.at(i).at(j) << " ";
    }
    cout << endl;
  }
  cout << "Total: " << result.size() << " sequences." << endl;
  return result;
}

// helper for isPureOSequence
bool isCorrectHVector (const vector<Monomial *>& socle, const vector<int>& candidate){
  const int length= candidate.size();
  int d = length-1;
  const int numvars = candidate[1];
  // Compute parts of the h-vector until the given sequence disagrees:
  vector<Monomial*> *currentLayer = listBelow(socle);
  vector<Monomial*> *next;
  unsigned long long numberOfMonomials;
  while (currentLayer->size() > 0) {
    d--;
    // cout << "Number of monomials" << numberOfMonomials << endl;
    // cout << "current->size() " << currentLayer->size() << endl;
    // printIntVector (candidate);
    // cout << candidate[d] << endl;
    if (currentLayer->size() != static_cast<unsigned int> (candidate[d])) {
      // can skip the rest of the computation, the h-vector does not
      // match anyway
      deleteVector (currentLayer); 
      return false;
    }
    numberOfMonomials = binomialCoefficient(numvars-1+d-1,numvars-1); // in the layer _below_
    // Apply the heuristics:
    if (currentLayer->size() > numberOfMonomials) { 
      // cout << "chose Pure ";
      next = listBelowPure (*currentLayer);
    }
    else  {
      // cout << "chose standard ";
      next = listBelow(*currentLayer);
    }
    deleteVector (currentLayer);
    currentLayer = next;
    // cut-off if all monomials in a level are exhausted we are done.
    if (next->size() == numberOfMonomials && next->size() == static_cast<unsigned int>(candidate[d-1])){
      deleteVector (next);
      return true; 
    }
  }
  cout << "WARNING, this point should not be reached " << endl;
  return true;
}

bool isPureOSequence (const vector<int>& candidate){
  // Need all combinations of type many monomials in numvars variables
  // of given degree
  const int length= candidate.size();
  const int degree = length-1;
  const int numvars = candidate[1];
  const int type = candidate[length-1];
  vector<Monomial*> *allMons = allMonomials(degree, numvars);
  Combinations C(type, allMons->size());
  vector<Monomial*> *currentSocle;
  unsigned long long todo = binomialCoefficient(allMons->size(),type);
  long counter = 0;
  do {
    // Informative output ?
    if (counter++ % 100000 == 0){
      cout << "Checking socle number " << counter << " out of " << todo << endl;
    }
    currentSocle = new vector<Monomial*>;
    for (int i=0; i<type; i++){
      currentSocle->push_back (allMons->at(C(i)));
    }
    // A shortcut to mod out some symmetry: We will skip every loop in
    // which the first monomial of the socle has an exponent vector
    // that is not weakly decreasing.
    if (!isWeaklyIncreasing ((*currentSocle)[0]->exponents)) { 
      delete currentSocle;
      continue;
    }
    if (isCorrectHVector (*currentSocle, candidate)) {
	cout << "The given vector is a pure O-sequence." << endl;
	cout << "Here is one socle that does it: " << endl;
	for (unsigned int i = 0; i<currentSocle->size(); i++){
	  cout << currentSocle->at(i)->toString() << endl;
	}
	delete currentSocle;
	deleteVector(allMons);
	return true;
      }
    delete currentSocle;
  } while (C.next());
  cout << "Enumeration complete.  The given sequence is not a pure O-sequence." << endl;
  deleteVector(allMons);
  return false;
}

inline
bool lastExponentSmaller (Monomial *m1, Monomial *m2){
  return ((*m1->exponents)[m1->length-1] > (*m2->exponents)[m1->length-1]);
}

// Maybe we need a total order later?
inline
bool backwardLexOrder (Monomial *m1, Monomial *m2) {
  for (unsigned int i = (m1->length)-1; i>=0; i--) {
    cout << i << endl;;
    if ((*m1->exponents)[i] > (*m2->exponents)[i]) {
      return true;
    }
    if ((*m1->exponents)[i] < (*m2->exponents)[i]) {
      return false;
    }
  }
  return true;
}

inline
bool isAdmissableCombination (const Combinations& c, const vector<int>& rightBoundaries) {
  // We are looking at combinations in binom (p-d, d) = binom (p,d)
  // Consider the equation:
  // bin(p,d) = 1 + bin {d+1,d-1} + bin {d+2,d-1} + ... + bin (p-1,d-1)
  // and bin the integers from 0 to bin(p,d) accordingly.
  // A combination is admissiable if it contains one element from each bin

  // For speed the bins are precompupted with another function and passed to here

  // We assume that the combination c is sorted.
  if (c(0) != 0) {return false;}
  for (unsigned int i = 1; i<rightBoundaries.size(); i++) {
    // Need to find one element in [ rightBoundaries[i-1] , rightBoundaries[i] ];
    bool intervalFound = false;
    for (unsigned int j=1; j<c.size(); j++){
      if ((c(j) > rightBoundaries[i-1]) && (c(j) <= rightBoundaries[i])) {
	// Found an element in the interval: Continue with next interval.
	// cout << "I claim that " << c(j) << " is in the interval (" << rightBoundaries[i-1] << "," << rightBoundaries[i] << "]"<<endl;
	intervalFound = true;
	break; // for loop over c
      }
    } // If this for loop ever finishes without breaking, the interval was not represented!
    if (!intervalFound) {
      return false;
    }
  }
  // c.display();
  return true;
}

vector< vector<int> > testAlexRecipe(const vector<int>& a, const int rank, const int type) {
  // Algorithm: for each permutation of the vector a 
  // enumerate all monomials in 
  vector<Monomial*> *allMons = allMonomials(a.size()-rank, rank);
  sort (allMons->begin(), allMons->end(), lastExponentSmaller); // Needed for the AdmissableBlocking later
  vector<int> rightBoundaries; // See isAdmissableCombination for explanations
  int sum=-1; // The first step will add 1 as a left boundary
  for (unsigned int i=rank-2; i <= a.size()-2; i++){
    sum+=binomialCoefficient(i, rank-2);
    rightBoundaries.push_back(sum);
  }
  Permutations P(a.size());  // Todo: Make a list of already seen permutations
  vector < vector <int> > hVectors; // Will store the result
  do { // for each permutation:
    vector<int> Pa(a.size());
    for (unsigned int i=0; i<a.size(); i++){
      Pa[i] = a[P(i)];
    }
    // for each permutation the result will be a vector of monomials:
    vector <Monomial*> *currentMonomials =  new vector<Monomial*>;
    for (unsigned int i=0; i < allMons->size(); i++) {
      const vector<int>& pattern = *(allMons->at(i)->exponents);
      vector<int>::const_iterator it = Pa.begin();
      vector<int> realexpo(rank);
      for (unsigned int j = 0; j<pattern.size(); j++) {
	int totake = pattern[j] + 1; // if the monomial contains a zero we have to take one.
	while (totake > 0) {
	  realexpo[j] += *it;
	  it++;
	  totake--;
	}
	realexpo[j] -= 1; // remember: a_i - 1
      }
      // printIntVector (realexpo);
      currentMonomials->push_back(new Monomial(realexpo));
    }
    // At this point we have completed the list of potential socle
    // monomials.  Now for every choice of type many we compute the
    // hVector and collect those:
    Combinations C(type, currentMonomials->size());
    vector<Monomial*> *currentSocle;
    do {
      if (!isAdmissableCombination(C, rightBoundaries)) {
	continue;
      }
      currentSocle = new vector<Monomial*>;
      for (int i=0; i<type; i++){
	currentSocle->push_back ((*currentMonomials)[C(i)]);
      }
      vector<int> h = hVector(*currentSocle);
      if (!isPresent (hVectors, h)) {
	  hVectors.push_back(h);
      }
      delete currentSocle;
    } while (C.next());
    deleteVector (currentMonomials);
  } while (P.next());
  deleteVector(allMons);
  // cout << "List of h vectors that were found :" << endl;
  // for (unsigned int i = 0; i<hVectors.size(); i++){
  //   printIntVector (hVectors[i]);
  // }
  // cout << endl;
  return hVectors;
}

inline long factorial(int x) {
  return (x == 1 ? x : x * factorial(x - 1));
}

bool isPureOSequenceAlexRecipe(const vector<int>& a, const int rank, const int type, const vector<int>& candidate){
  vector<Monomial*> *allMons = allMonomials(a.size()-rank, rank);
  sort (allMons->begin(), allMons->end(), lastExponentSmaller); // Needed for the AdmissableBlocking later
  vector<int> rightBoundaries; // See isAdmissableCombination for explanations
  int sum=-1; // The first step will add 1 as a left boundary
  for (unsigned int i=rank-2; i <= a.size()-2; i++){
    sum+=binomialCoefficient(i, rank-2);
    rightBoundaries.push_back(sum);
  }
  Permutations P(a.size());  // Later: not all permutations are needed
  long permnumber = factorial (a.size());
  long permcounter = 0;
  vector< vector<int> > seenPermutations;
  // e.g. if there are duplicate entries in a -> keep a list of seen a-vectors
  do { // for each permutation:
    permcounter++;
    vector<int> Pa(a.size());
    for (unsigned int i=0; i<a.size(); i++){
      Pa[i] = a[P(i)];
    }
    if (!isPresent(seenPermutations, Pa) ) {
      seenPermutations.push_back(Pa);
    } 
    else {
      cout << "Skipped a permutation" << endl;
      continue;
    }
    // for each permutation the result will be a vector of monomials:
    vector <Monomial*> *currentMonomials =  new vector<Monomial*>;
    for (unsigned int i=0; i < allMons->size(); i++) {
      const vector<int>& pattern = *(allMons->at(i)->exponents);
      vector<int>::const_iterator it = Pa.begin();
      vector<int> realexpo(rank);
      for (unsigned int j = 0; j<pattern.size(); j++) {
	int totake = pattern[j] + 1; // if the monomial contains a zero we have to take one.
	while (totake > 0) {
	  realexpo[j] += *it;
	  it++;
	  totake--;
	}
	realexpo[j] -= 1; // remember: a_i - 1
      }
      // printIntVector (realexpo);
      currentMonomials->push_back(new Monomial(realexpo));
    }
    // At this point we have completed the list of potential socle
    // monomials.  Now for every choice of type many we compute the
    // hVector and collect those:
    Combinations C(type, currentMonomials->size());
    vector<Monomial*> *currentSocle;
    unsigned long todoitems = binomialCoefficient(currentMonomials->size(),type);
    unsigned long counter = 0;
    do {
      if (counter++ % 100000==0){
	cout << "Now doing " << counter << " out of " << todoitems << " for permutation no. " 
	     << permcounter << " of " << permnumber << endl;
      }
      if (!isAdmissableCombination(C, rightBoundaries)) {
	continue;
      }
      currentSocle = new vector<Monomial*>;
      for (int i=0; i<type; i++){
	currentSocle->push_back ((*currentMonomials)[C(i)]);
      }
      if (isCorrectHVector(*currentSocle, candidate)){
	// done
	cout << "Found a socle that does it:" << endl;
	for (unsigned int i = 0; i<currentSocle->size();i++){
	  printIntVector (*(currentSocle->at(i)->exponents));
	}
	delete currentSocle;
	deleteVector (currentMonomials);
	deleteVector(allMons);
	return true;
      }
      delete currentSocle;
    } while (C.next());
    deleteVector (currentMonomials);
  } while (P.next());
  deleteVector(allMons);
  return false;
}

void listOrderIdeals (const int degree, const int type, const int numvars, const vector<int>& hV){
  // Need all combinations of type many monomials in numvars variables
  // of given degree
  vector<Monomial*> *allMons = allMonomials(degree, numvars);
  Combinations C(type, allMons->size());
  vector<Monomial*> *currentSocle;
  vector< vector<Monomial*>* > result;
  unsigned long todo = binomialCoefficient(allMons->size(),type);
  unsigned long counter = 0;
  do {
//     // Informative output ?
    if (counter++ % 100000 == 0){
      cout << "Checking socle number " << counter << " out of " << todo << endl;
    }
    currentSocle = new vector<Monomial*>;
    for (int i=0; i<type; i++){
      currentSocle->push_back (allMons->at(C(i)));
    }
//     cout << "Current socle" << endl;
//     for (unsigned int i=0; i< currentSocle->size(); i++){
//       cout << currentSocle->at(i)->toString() << endl;
//     }
//     cout << "-----------------------------" << endl;
    vector<int> h = hVector(*(currentSocle));
    if (h == hV) {
      result.push_back(currentSocle);
      cout << "Found an instance! Count so far: " << result.size() << endl;
    }
    else { delete currentSocle; }
    } while (C.next());
  for (unsigned int i = 0; i <  result.size(); i++){
    for (unsigned int j = 0; j <  result.at(i)->size(); j++){
      cout << result.at(i)->at(j)->toString() << endl;
    }
    cout << endl;
    cout.flush();
  }
}

vector<int> differenceVector (const vector<int>& h){
  vector<int> result; 
  result.push_back(1);
  for (unsigned int i=0; i<h.size()-1; i++){
    result.push_back (h[i+1] - h[i]);
  }
  return result;
}

bool differenceCondition (const vector<int>& h1, const vector<int>& h2){
  // h1 is the longer vector and supposed to be bigger
  vector<int> dh1 = differenceVector (h1);
  vector<int> dh2 = differenceVector (h2);
  for (unsigned int i =0; i< (h1.size()/2)+1; i++) {
    if (dh1[i] < dh2[i]) return false;
  }
  return true;
}

bool sizeCondition (const vector<int>& h1, const vector<int>& h2){
  for (unsigned int i =0; i< (h1.size()/2)+1; i++) {
    if (h1[i] < h2[i]) return false;
  }
  return true;
}

vector<int> sumShifted (const vector<int>& h1, const vector<int>& h2){
  assert(h1.size() == h2.size()+1);
  vector<int> result;
  result.push_back(h1[0]);
  for (unsigned int i = 0; i<h2.size(); i++){
    result.push_back(h1[i+1]+h2[i]);
  }
  return result;
}

struct counterexample{
  vector<int> h1;
  vector<int> h2;
  vector<int> sum;
};
  
void testAdditivityConjecture (const int e){
  // Test Conjecture 3.1. in Stokes, Zanello, et al.
  // 4 4 4 ran through
  int degree = 5;
  int type = 5;
  int numvars = 4;
  vector < vector <int> > longsequences = enumeratePureOSequences (degree, type, numvars);
  vector < vector <int> > shortsequences = enumeratePureOSequences (degree-1, type, numvars);
  int pos=0;
  int neg=0;
  vector <counterexample*> *ce = new vector<counterexample*>;
  counterexample *cp;
  for (unsigned int i=0; i<longsequences.size(); i++){
    for (unsigned int j=0; j<shortsequences.size(); j++){
      if (differenceCondition (longsequences[i],shortsequences[j]) && sizeCondition (longsequences[i], shortsequences[j])) {
	if (isPureOSequence (sumShifted (longsequences[i], shortsequences[j]))){
	  pos++;
	  cout << "Number of examples: " << pos << endl;
	  cout << "Number of counterexamples: " << neg << endl;
	}
	else {
	  neg++;
	  cout << "Number of counterexamples: " << neg << endl;
	  cp = new counterexample;
	  cp->h1 = longsequences[i];
	  cp->h2 = shortsequences[j];
	  cp->sum = sumShifted(longsequences[i], shortsequences[j]);
	  ce->push_back(cp);
	  cout << "Counterexample no " << neg <<":" << endl;
	  cout << "First h-vector:" << endl;
	  printIntVector(cp->h1);
	  cout << "Second h-vector:" << endl;
	  printIntVector(cp->h2);
	  cout << "Shifted sum of h-vectors:" << endl;
	  printIntVector(cp->sum);
	  cout << "----------------";
	  cout << endl;
	}
      }
    }
  }
  for (unsigned int i=0; i< ce->size(); i++){
    cout << "Counterexample no " << i+1 <<":" << endl;
    cout << "First h-vector:" << endl;
    printIntVector((*ce)[i]->h1);
    cout << "Second h-vector:" << endl;
    printIntVector((*ce)[i]->h2);
    cout << "Shifted sum of h-vectors:" << endl;
    printIntVector((*ce)[i]->sum);
    cout << "----------------";
    cout << endl;
  }
  // assert(differenceCondition (h1,h2));
  // assert(isPureOSequence (sumShifted (h1, h2)));
}
