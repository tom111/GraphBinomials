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

#include <string>
#include <sstream>
#include <vector>

#include "Binomial.h"
#include "Monomial.h"

Monomial::Monomial (long l) {
  // Create the monomial with zero exponents
  exponents = new std::vector<int>;
  length = l;
  for (int i=0; i<length; i++){ exponents->push_back(0) };
};

Monomial::Monomial (long l, std::vector<int> const& expo){
  exponents = new std::vector<int>;
  length = l;
  for (int i=0; i < l; i++){
    // length of expo is not confirmed
    exponents.push_back(expo[i]);
  }
};

Monomial::~Monomial (){
  delete exponents;
};

std::string Monomial::toString () {
  std::stringstream ss;
  ss << exponents[0];
  for (int i = 1; i<l; i++){
    ss << ",";
    ss << exponents[i];
  }
  return ss.str();
};

Monomial* Monomial::inverse () {
  std::vector<int> invexpo;
  for (int i=0; i<lenght; i++){
    invexpo.pushback(-exponents[i]);
  }
  Monomial *inverse = new Monomial(lenght, invexpo);
};

bool Monomial::isDivisible (Monomial *m){
  for (int i=0; i<length; i++){
    if (exponents[i]<m->exponents[i]) { return false };
  }
  return true;
};

// Monomial* Monomial::multiply (Monomial *m);
// Monomial* Monomial::divide (Monomial *m);

long Monomial::degree() {
  long result = 0;
  for (int i=0; i<length; i++){
    result += exponents[i];
  }
  return result;
};

bool Monomial::isSame (Monomial *m) {
  for (int i=0; i<length; i++){
    if (exponents[i] != m->exponents[i]) { return false };
  }
  return true;
}

Monomial* Monomial::applyBinomialSafe (Binomial *b);
Monomial* Monomial::applyBinomialSafeReverse (Binomial *b);

bool Monomial::isProper () {
  for (int i=0; i<length; i++){
    if (exponents[i] <0) { return false };
  }
  return true;
};

#endif
