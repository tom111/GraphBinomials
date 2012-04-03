""" Implementation of the main algorithms"""

# General python import
from itertools import combinations

# The monomial tools
from monomial import *

## Getting unique elements of a list ##
def unique(seq, idfun=None):
    """Returns the unique elements in a list
    order preserving"""
    if idfun is None:
        def idfun(x): return x
    seen = {}
    result = []
    for item in seq:
        marker = idfun(item)
        # in old Python versions:
        # if seen.has_key(marker)
        # but in new ones:
        if marker in seen: continue
        seen[marker] = 1
        result.append(item)
    return result

def neighbors (mons, binomials):
    """ Takes a list of monomials and produces their neighbors"""
    result = []
    for m in mons:
        for b in binomials:
            try:
                result.append(m.applyBinomialSafe(b))
            except NotApplicable:
                pass
            # Also need to try in the other direction
            try:
                result.append(m.applyBinomialSafe(b.invert()))
            except NotApplicable:
                pass
    return unique (result, idfun=lambda m: str(m.exponents))

def isPresent (l, m):
    """Check if a monomial m is present in a list l"""
    for li in l:
        if li.isSame(m): return True
    return False

def enumerateConnectedComponent (m, binomials, Verbose=False):
    """ Starting from a monomial m, perform a breadth first exploration of the
    connected component"""
    if Verbose:
        print ("Starting breadth-first exploration of connected component")
    result = [m]
    # This will store previously unseen elements in the next neighborhood
    newKids = [m] 
    while len (newKids) > 0:
        newneighbors = neighbors (newKids, binomials)
        # Sort the new neighbors into newKids and oldKids
        newKids = []
        for n in newneighbors:
            if not isPresent (result, n):
                newKids.append(n)
                result.append(n)
        if newKids != []:
            print ("Next iteration will run with " + str(len(newKids)) + " new neighbours.")
        else: 
            if Verbose: print ("Done :)")
    return result

def inSameComponent (m1, m2, binomials, Verbose=False):
    """
    Check if two monomials m1, m2 can be connected via the given binomials

    Use breadth-first like in enumeration of a connected component
    """
    if Verbose: print ("Starting breadth-first exploration of connected component")
    # This will store all seen monomials
    known = [m1]
    # This will store previously unseen elements in the next neighborhood
    newKids = [m1] 
    while len (newKids) > 0:
        newneighbors = neighbors (newKids, binomials)
        # Sort the new neighbors into newKids and oldKids
        newKids = []
        for n in newneighbors:
            if n.isSame (m2):
                return True
            if not isPresent (known, n):
                newKids.append(n)
                known.append(n)
        if newKids != []:
            if Verbose:
                print ("Next iteration will run with " + str(len(newKids)) + " new neighbours.")
        else: 
            if Verbose: print ("Done :)")
    return False

def isIsolated (m, binomials):
    """
    Check if a monomial m is isolated via the given edges
    """
    for b in binomials:
        try:
            m.applyBinomialSafe(b)
            # This will either succeed or throw the NotApplicable exception
            return False
        except NotApplicable:
            pass
        # Also need to try in the other direction
        try:
            m.applyBinomialSafe(b.invert())
            return False
        except NotApplicable:
            pass
    # None of the binomials applied
    return True

def axisSaturate (binomials, i, degree, Verbose=False):
    """
    TODO: Think about termination issue

    Compute the axis saturation with respect to variable index i, terminating
    at a given search degree.

    Algorithm:
    
    For each degree:

      consider all pairs of monomials both divisible by the variable in index
      i and check whether they can be connected, while the divided monomials
      can't be connected.
    """
    result = [b for b in binomials]
    # This is again assumed to be a constant over all binomials, but not
    # checked.
    length = binomials[0].length
    d = 1;
    while d < degree:
        if Verbose: print ("Now searching for degree " + str (d) + " moves.")
        # List monomials of degree d, divisible by i.
        mi = monomial(length, exponents = [1 if j==i else 0 for j in range (length)])
        divisibleMonomials = listDivisibleMonomials (d+1, mi, length)
        # Filter the isolated Monomials:
        if Verbose: print ("Filtering isolated monomials")
        divisibleMonomials = [m for m in divisibleMonomials if not isIsolated (m, result)]
        if Verbose: print ("Done")
        if Verbose:
            n = len (divisibleMonomials)
            numpairs = n*(n-1)/2
            print ("There are " + str (numpairs) + " pairs to investigate.")
        # Get an iterator of the pairs
        pairs = combinations(divisibleMonomials, 2)
        counter = 0;
        for p in pairs:
            counter = counter + 1
            if Verbose and counter%100 == 0:
                print (str(counter) + " pairs done.")
            # Check if they are in the same connected component via the current result
            if inSameComponent (p[0], p[1], result):
                # Check if the divided monomials were already connected
                if not inSameComponent(p[0].divide(mi), p[1].divide(mi), result):
                    # Found a new element
                    newbinomial = p[0].divide(p[1])
                    print ("Found element of the saturation: ")
                    print newbinomial
                    result.append (newbinomial)
        d=d+1
    return result

