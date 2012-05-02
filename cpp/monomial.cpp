/*
 *  Monomial.cpp
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
#include <string>
#include <sstream>
#include <vector>

#include "binomial.h"
#include "monomial.h"

using namespace std;

Monomial::Monomial (long llength) : length(llength) {
  // Create the monomial with zero exponents
  exponents = new vector<int>;
  for (int i=0; i<length; i++){ exponents->push_back(0); };
};

Monomial::Monomial (long llength, const vector<int>& expo) : length(llength) {
  exponents = new vector<int>;
  for (int i=0; i < length; i++){
    // length of expo is not confirmed
    exponents->push_back(expo[i]);
  }
};

Monomial::Monomial (const vector<int>& expo) : length(expo.size()) {
  exponents = new vector<int>;
  for (int i=0; i < length; i++){
    // length of expo is not confirmed
    exponents->push_back(expo[i]);
  }
}

Monomial::Monomial (const string& s) {
    // This constructor assumes the string s is a single line containing space
  // separated values of the exponent vector.
  istringstream ss (s);
  string word;
  exponents = new vector<int>;
  while ( ss >> word ) {
    exponents->push_back(atoi(word.c_str()));
  };
  length = exponents->size();
}

Monomial::Monomial (const Monomial& m) : length(m.length){
  // Copy the given monomial using the copy constructor of std::vector
  exponents = new vector<int>(*m.exponents);
};

Monomial::~Monomial (){
  delete exponents;
};

string Monomial::toString () const {
  stringstream ss;
  ss << (*exponents)[0];
  for (int i = 1; i<length; i++){
    ss << ",";
    ss << (*exponents)[i];
  }
  return ss.str();
};

Monomial* Monomial::inverse () const {
  vector<int> invexpo;
  for (int i=0; i<length; i++){
    invexpo.push_back(-(*exponents)[i]);
  }
  return new Monomial(length, invexpo);
};

bool Monomial::isDivisible (const Monomial& m) const {
  for (int i=0; i<length; i++){
    if ( (*exponents)[i] < (*m.exponents)[i] ) { return false; };
  };
  return true;
};

Monomial* Monomial::multiply (const Monomial& m) const {
  vector<int> newexpo;
  for (int i=0; i<length; i++){
    newexpo.push_back((*exponents)[i] + (*m.exponents)[i]);
  }
  return new Monomial (length, newexpo);
}
// Monomial* Monomial::divide (Monomial *m);

long Monomial::degree() const {
  long result = 0;
  for (int i=0; i<length; i++){
    result += (*exponents)[i];
  }
  return result;
};

bool Monomial::operator== (const Monomial& m) const {
  if (length != m.length) return false;
  for (int i=0; i<length; i++){
    if ( (*exponents)[i] != (*m.exponents)[i]) { return false; };
  };
  return true;
}

Monomial* Monomial::applyBinomialSafe (const Binomial& b) const {
  vector<int> newexpo;
  for (int i=0; i<length; i++){
    // Compute the exponent vector
    if ( (*exponents)[i] - (*b.head->exponents)[i] < 0) {
      throw "Not applicable";
    }
    else {
      newexpo.push_back((*exponents)[i] -
			(*b.head->exponents)[i] +
			(*b.tail->exponents)[i]);
    };
  };
  return new Monomial(length, newexpo);
};


Monomial* Monomial::applyBinomialSafeReverse (const Binomial& b) const {
  vector<int> newexpo;
  for (int i=0; i<length; i++){
    // Compute the exponent vector
    if ((*exponents)[i] - (*b.tail->exponents)[i] < 0) {
      throw "Not applicable";
    }
    else {
      newexpo.push_back((*exponents)[i] +
			(*b.head->exponents)[i] -
			(*b.tail->exponents)[i]);
    };
  };
  return new Monomial(length, newexpo);
}

bool Monomial::isProper () const {
  for (int i=0; i<length; i++){
    if ( (*exponents)[i] <0) { return false; };
  }
  return true;
};
