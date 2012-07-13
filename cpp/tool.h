// Copyright (C) 2012 Thomas Kahle
// Licenced under the GPL version 2 or later
#ifndef SWISSTOOL_H
#define SWISSTOOL_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

inline
vector<int> stringToVector (const string s){
  istringstream ss (s);
  string word;
  vector<int> res;
  while ( ss >> word ) {
    res.push_back(atoi(word.c_str()));
  };
  return res;
}

inline
void printIntVector (const vector<int>& v){
  for (unsigned int i =0; i < v.size(); i++){
    cout << v[i] << " ";
  }
  cout << endl;
}

inline
bool isPresent (const vector< vector<int> >& list, const vector<int>& element){
  for (unsigned int i=0; i<list.size(); i++){
    if (element==(list[i])) {
      return true;
    };
  };
  return false;
};

// Todo, make templates:
inline
bool sameListOfMonomials (const vector<Monomial*>& l1, const vector<Monomial*>& l2) {
  // Check if two lists of monomials are the same by checking if each element
  // of either list is present in the other list.
  for (unsigned int i=0; i<l1.size(); i++){
    if (!isPresent(l2, *l1[i])) { return false; }
  }
  for (unsigned int i=0; i<l2.size(); i++){
    if (!isPresent(l1, *l2[i])) { return false; }
  }
  return true;
}

inline 
bool sameListsOfIntVectors (const vector< vector<int> >& l1, const vector< vector<int> >& l2) {
  for (unsigned int i=0; i<l1.size(); i++){
    if (!isPresent(l2, l1[i])) { return false; }
  }
  for (unsigned int i=0; i<l2.size(); i++){
    if (!isPresent(l1, l2[i])) { return false; }
  }
  return true;
}

inline
bool isWeaklyIncreasing (const vector<int> *v) {
  for (unsigned int i=0; i<v->size()-1; i++){
    if (v->at(i) > v->at(i+1)){
      return false;
    }
  }
  return true;
}

template <class T>
inline void deleteVector (vector<T*> *v) {
  for (unsigned int i=0; i<v->size(); i++){
    delete (*v)[i];
  }
  delete v;
}


#endif
