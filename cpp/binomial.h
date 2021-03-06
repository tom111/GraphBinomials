/*
 *  Binomial.h 
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
#ifndef BINOMIAL_H
#define BINOMIAL_H

#include <vector>
#include <string>

#include "monomial.h"

class Binomial {

 public:
  Monomial *head;
  Monomial *tail;
  
  /*
    A Binomial is unital and thus consists of its two monomials.  The Binomial
    owns the two monomials, that is they are created upon creation of the
    monomial and freed at the end of its lifetime.  Construction is via one or
    two exponent vectors or directly via monomials
   */
  Binomial (const std::vector<int>& exponents); // integer exponents
  Binomial (const std::vector<int>& headExp, const std::vector<int>& tailExp); // non-negative exponents
  Binomial (const Monomial& hd, const Monomial& tl); // two monomials
  Binomial (const std::string& s); // read exponent vector from string
  Binomial (const Binomial& b); // copy
  ~Binomial ();
  unsigned int degree() const;
  std::string toString() const;
  Binomial* multiply (const Monomial& m) const;
};

#endif
