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

inline unsigned long binomialCoefficient (int N, int k) {
  if (k<0) {return 0;};
  if (k>N) {return 0;};
  if ((N-k) < k) { k = N-k;}
  int result = 1;
  for (int i=1; i < k+1; i++){
    result *= N-k+i;
    result /= i;
  }
  return result;
}

vector<int> hVector (const vector<Monomial*>& mons);

void enumeratePureOSequences (const int degree, const int type, const int numvars);
void isPureOSequence (const vector<int>& candidate);
void listOrderIdeals (const int degree, const int type, const int numvars, const vector<int>& hV);

// vector<Monomial*>* orderIdeal (const std::vector<Monomial*>& gens);

#endif
