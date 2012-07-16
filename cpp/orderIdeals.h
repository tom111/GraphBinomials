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

vector < vector<int> > enumeratePureOSequences (const int degree, const int type, const int numvars);
bool isPureOSequence (const vector<int>& candidate);
vector< vector<int> > testAlexRecipe(const vector<int>& a, const int rank, const int type);
bool isPureOSequenceAlexRecipe(const vector<int>& a, const int rank, const int type, const vector<int>& candidate);
void listOrderIdeals (const int degree, const int type, const int numvars, const vector<int>& hV);
vector<int> differenceVector (const vector<int>& h);
bool differenceCondition (const vector<int>& h1, const vector<int>& h2);
void testAdditivityConjecture (const int e);

// vector<Monomial*>* orderIdeal (const std::vector<Monomial*>& gens);

#endif
