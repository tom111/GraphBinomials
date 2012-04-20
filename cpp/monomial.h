/*
 *  Monomial.h 
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
#ifndef MONOMIAL_H
#define MONOMIAL_H

#include <string>
#include <vector>


// Forward reference to Binomial
class Binomial;

/*
A monomial is a minimalistic data structure consisting basically only of an
exponent vector and its length

Monomials are implemented immutable, they copy a given exponent vector on
creation */

class Monomial {
 
 public:
  long length;
  std::vector<int> *exponents;
  // exponents should not be too big, so we can save a little memory here by
  // using int instead of long

  // The identity monomial constructor
  Monomial (long length);
  // A special monomial constructor
  Monomial (long length, std::vector<int> exponents);
  ~Monomial ();

  // std::Vector<int> getExponents ();
  std::string toString ();
  Monomial* inverse ();
  bool isDivisible (Monomial *m);
  //  Monomial* multiply (Monomial *m);
  //  Monomial* divide (Monomial *m);
  long degree();

  bool isSame (Monomial *m);
  Monomial* applyBinomialSafe (Binomial *b);
  Monomial* applyBinomialSafeReverse (Binomial *b);
  bool isProper ();

};

#endif
