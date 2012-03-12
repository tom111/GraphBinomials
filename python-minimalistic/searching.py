""" Implementation of the main algorithms"""

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

def enumerateConnectedComponent (m, binomials):
    """ Starting from a monomial m, perform a breadth first exploration of the
    connected component"""
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
        else: print ("Done :)")
    return result

def inSameComponent (m1, m2, binomials):
    """
    Check if two monomials m1, m2 can be connected via the given binomials

    Use breadth-first like in enumeration of a connected component
    """
    print ("Starting breadth-first exploration of connected component")
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
            print ("Next iteration will run with " + str(len(newKids)) + " new neighbours.")
        else: print ("Done :)")
    return False

