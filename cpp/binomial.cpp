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

#include <vector>
#include "monomial.h"
#include "binomial.h"

using namespace std;

Binomial::Binomial (vector<int> exponents) {
  // Create a binomial from an integer vector
  vector<int> headexp;
  vector<int> tailexp;
  for (int i=0; i<exponents.size(); i++) {
    if ( exponents[i] > 0 ) {
      // This becomes the tail
      headexp.push_back(exponents [i]);
      tailexp.push_back(0);
    }
    else {
      headexp.push_back(0);
      tailexp.push_back(-exponents[i]);
    };
  };
  head = new Monomial (exponents.size(), headexp);
  tail = new Monomial (exponents.size(), tailexp);
}

Binomial::Binomial (vector<int> headExp, std::vector<int> tailExp) {
  head = new Monomial (exponents.size(), headExp);
  tail = new Monomial (exponents.size(), tailExp);
}

Binomial::Binomial (Monomial *hd, Monomial* tl) {
  // Will copy the monomials
  head = new Monomial (hd);
  tail = new Monomial (tl);
}

Binomial::~Binomial ();


