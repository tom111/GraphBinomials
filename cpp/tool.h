#include <cstdlib>
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

