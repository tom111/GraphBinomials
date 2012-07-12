// (c) 2012 Thomas Kahle
// GPL Version 2 or later at your choice.

#ifndef PERMUTATIONS_H
#define PERMUTATIONS_H

#include <algorithm>
#include <iostream>
#include <vector>

// a class to iterate through m combinations out of n
// simple wrapper around nextPermutation from STL
class Permutations
{
 public:
  
  Permutations(int m) : m_(m) {
    permutation_.resize(m);
    for (int i = 0; i < m_; i++) permutation_[i] = i;
  }

  int next()
  {
    return next_permutation (permutation_.data(),permutation_.data()+m_);
  }
  
  int operator() (int i)
  {
    if (i < m_) return permutation_[i];
    return -1;
  }

  int size()
  {
    return permutation_.size();
  }

  void display()
  {
    for (int i = 0; i < m_; i++)
      {
	std::cout << permutation_[i] << " ";
      }
    std::cout << std::endl;
  }

 private:
  int m_;
  std::vector<int> permutation_;
};

#endif
