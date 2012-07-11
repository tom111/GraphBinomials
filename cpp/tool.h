#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

vector<int> stringToVector (const string s){
  istringstream ss (s);
  string word;
  vector<int> res;
  while ( ss >> word ) {
    res.push_back(atoi(word.c_str()));
  };
  return res;
}

void printIntVector (const vector<int>& v){
  for (unsigned int i =0; i < v.size(); i++){
    cout << v[i] << " ";
  }
  cout << endl;
}
