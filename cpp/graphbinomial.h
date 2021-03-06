/*
 *  graphbinomial.h 
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
#ifndef GRAPHBINOMIAL_H
#define GRAPHBINOMIAL_H

#include "monomial.h"
#include "binomial.h"

#include <vector>

using namespace std;

std::vector<Monomial*>* generateNeighbours (const vector<Monomial>& base, const vector<Binomial>& steps);
bool inSameComponent (const Monomial& m1, const Monomial& m2, const vector<Binomial>& moves);
std::vector<Monomial*>* enumerateComponent (const Monomial& m, const std::vector<Binomial>& moves);

#endif
