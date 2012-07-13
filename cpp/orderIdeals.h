/*
 *  orderIdeals.h 
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
#ifndef ORDERIDEALS_H
#define ORDERIDEALS_H

#include <vector>

#include "monomial.h"
#include "graphbinomial.h"

using namespace std;

vector<Monomial*>* listBelow (const std::vector<Monomial*>& mons); 
vector<Monomial*>* allMonomials (const int degree, const int numvars);

vector<int> hVector (const vector<Monomial*>& mons);

void enumeratePureOSequences (const int degree, const int type, const int numvars);
bool isPureOSequence (const vector<int>& candidate);
vector< vector<int> > testAlexRecipe(const vector<int>& a, const int rank, const int type);
bool isPureOSequenceAlexRecipe(const vector<int>& a, const int rank, const int type, const vector<int>& candidate);
void listOrderIdeals (const int degree, const int type, const int numvars, const vector<int>& hV);

inline
bool isAdmissableCombination (const vector<int>& c, const vector<int>& rightBoundaries) {
  // We are looking at combinations in binom (p-d, d) = binom (p,d)
  // Consider the equation:
  // bin(p,d) = 1 + bin {d+1,d-1} + bin {d+2,d-1} + ... + bin (p-1,d-1)
  // and bin the integers from 0 to bin(p,d) accordingly.
  // A combination is admissiable if it contains one element from each bin

  // For speed the bins are precompupted with another function and passed to here

  // We assume that the combination c is sorted.
  if (c[0] != 1) {return false;}
  for (unsigned int i = 1; i<rightBoundaries.size(); i++) {
    // Need to find one element in [ rightBoundaries[i-1] , rightBoundaries[i] ];
    bool intervalFound = false;
    for (unsigned int j=1; j<c.size(); j++){
      if (c[j] > rightBoundaries[i-1] && c[j] <= rightBoundaries[i]) {
	// Found an element in the interval: Continue with next interval.
	intervalFound = true;
	break; // for loop over c
      }
    } // If this for loop ever finishes without breaking, the interval was not represented!
    if (!intervalFound) {
      return false;
    }
  }
  return true;
}

// vector<Monomial*>* orderIdeal (const std::vector<Monomial*>& gens);

#endif
