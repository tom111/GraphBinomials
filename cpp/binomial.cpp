/*
 *  Binomial.cpp
 *
 *  Copyright (C) 2012 Thomas Kahle
 *  <thomas-kahle@gmx.de>
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or (at
 *  your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "monomial.h"
#include "binomial.h"

using namespace std;

Binomial::Binomial (const vector<int>& exponents) {
  // Create a binomial from an integer vector
  vector<int> headexp;
  vector<int> tailexp;
  for (unsigned int i=0; i<exponents.size(); i++) {
    if ( exponents[i] > 0 ) {
      // Push exponent to the head and a zero to the tail
      headexp.push_back(exponents[i]);
      tailexp.push_back(0);
    }
    else {
      // vice versa
      headexp.push_back(0);
      tailexp.push_back(-exponents[i]);
    };
  };
  head = new Monomial (headexp);
  tail = new Monomial (tailexp);
}

Binomial::Binomial (const vector<int>& headExp, const std::vector<int>& tailExp) {
  head = new Monomial (headExp);
  tail = new Monomial (tailExp);
}

Binomial::Binomial (const Monomial& hd, const Monomial& tl) {
  // Will copy the monomials
  head = new Monomial (hd);
  tail = new Monomial (tl);
}

Binomial::Binomial (const std::string& s){
  // This constructor assumes the string s is a single line containing space
  // separated values of the exponent vector.
  std::istringstream ss (s);
  std::string word;
  std::vector<int> exponents;
  while ( ss >> word ) {
    exponents.push_back(atoi(word.c_str()));
  };
  // Can't call other constructor from here in C++
  // duplicate code from above
  vector<int> headexp;
  vector<int> tailexp;
  for (unsigned int i=0; i<exponents.size(); i++) {
    if ( exponents[i] > 0 ) {
      // Push exponent to the head and a zero to the tail
      headexp.push_back(exponents[i]);
      tailexp.push_back(0);
    }
    else {
      // vice versa
      headexp.push_back(0);
      tailexp.push_back(-exponents[i]);
    };
  };
  head = new Monomial (headexp);
  tail = new Monomial (tailexp);
}

Binomial::Binomial (const Binomial& b) { 
  head = new Monomial (*b.head);
  tail = new Monomial (*b.tail);
}

Binomial::~Binomial () {
  delete head;
  delete tail;
}

unsigned int Binomial::degree () const {
  unsigned int d1 = head->degree() , d2 = tail->degree();
  if (d1 != d2) {
    cout << "Warning, not homogeneous";
    return -1;
  }
  else return d1;    
}

