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
