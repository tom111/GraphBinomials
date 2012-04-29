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
  // Todo: Decide on a public and private interface separation
 public:
  long length;
  std::vector<int> *exponents;
  // exponents should not be too big, so we can save a little memory here by
  // using int instead of long

  Monomial (long llength);
  Monomial (long llength, const std::vector<int>& exponents);
  Monomial (const std::vector<int>& expo);
  Monomial (const Monomial& m);
  ~Monomial ();

  // std::Vector<int> getExponents ();
  std::string toString () const;
  Monomial* inverse () const;
  bool isDivisible (const Monomial& m) const;
  Monomial* multiply (const Monomial& m) const;
  //  Monomial* divide (Monomial *m);
  long degree() const;

  bool operator== (const Monomial& m) const;
  Monomial* applyBinomialSafe (const Binomial& b) const;
  Monomial* applyBinomialSafeReverse (const Binomial& b) const;
  bool isProper () const;
};

#endif
