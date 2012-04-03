"""
A monomial is a minimalistic data structure consisting of an exponent vector.
At some point we may even switch to some smaller self-managed binary coding,
but int will do for now.

Monomials are implemented almost immutable.  We can set their exponents, but
otherwise all operations create new monomials.
"""

# Sage 
from sage.all import IntegerVectors

# Cython 
from libcpp.vector cimport vector
from cython.operator import dereference as deref, preincrement as inc

# Exceptions:
class LengthMismatch (Exception):
    """Exception to indicate that a given exponent vector does not fit this
    monomial"""
    pass

class NotApplicable (Exception):
    pass

cdef vector[int] convertIntVector (v):
    cdef vector[int] result
    for vv in v:
        result.push_back(v)

# The monomial class

# The class is still immutable, that is it returns new objects everytime we
# divide, invert, ...

# Implementation details: Some external vector<int> is copied upon creation of
# a monomial.  Like this the external code need not manage the int vectors.

cdef class Monomial(object):
    cdef public int length  # Public makes this python accessible
    cdef vector[int] *exponents # Can't make this public because vector[int] can't be converted to python

    def __cinit__(self):
        self.exponents = new vector[int]()

    def __init__(self, int length, exponents):
        """Will copy the given python list of exponents"""
        self.length=length
        for i in range(length):
            self.exponents.push_back(exponents[i])

    def __dealloc__ (self):
        del self.exponents

    def __str__ (self):
        cdef vector[int].iterator it = self.exponents.begin()
        output = ""
        while it != self.exponents.end():
            output = output+" "+ str(deref(it))
            inc(it)
        return output
    
    def inverse(self):
        result = []
        cdef vector[int].iterator it = self.exponents.begin()
        while it != self.exponents.end():
            result.append(-deref(it))
            inc(it)
        return Monomial(self.length, result)

    def isDivisible (self, Monomial m):
        if m.length==self.length:
            for i in range(self.length):
                if self.exponents.at(i) < m.exponents.at(i):
                    return False
            return True
        else:
            raise LengthMismatch()

    def multiply (self, Monomial m):
        if m.length==self.length:
            return Monomial(self.length, [self.exponents.at(i) + m.exponents.at(i) for i in range (self.length)])
        else:
            raise LengthMismatch()

    def divide (self, Monomial m):
        if m.length==self.length:
            return Monomial(self.length, [self.exponents.at(i) - m.exponents.at(i) for i in range (self.length)])
        else:
            raise LengthMismatch()

    def positivePart (self):
        cdef int v
        result =[]
        for i in range (self.length):
            v = self.exponents.at(i)
            result.append(max(v, 0))
        # The following generates invalid c++ code
        # result = [max(self.exponents.at(i), j) for i in range (self.length)]
        return Monomial (self.length, result)

    def negativePart (self):
        cdef int v
        result =[]
        for i in range (self.length):
            v = self.exponents.at(i)
            result.append(max(-v, 0))
        return Monomial (self.length, result)

    def degree (self):
        cdef int result
        cdef vector[int].iterator it = self.exponents.begin()
        while it != self.exponents.end():
            result = result + deref(it)
            inc(it)
        return result

    def applyBinomial(self, b):
        raise NotImplementedError()

    def applyBinomialSafe (self,b):
        if self.length != b.length: raise LengthMismatch()
        resultExponents = [0 for i in range (self.length)]
        for i in range (self.length):
            if self.exponents.at(i) < b.exponents.at(i): raise NotApplicable()
            resultExponents[i] = self.exponents.at(i) - b.exponents.at(i)
        return Monomial(self.length, resultExponents)

    def isProper (self):
        return self.isDivisible(Monomial(self.length), [0 for i in range(self.length)])

    # Todo, implement proper comparison operator
    def isSame (self, Monomial m):
        if not m.length == self.length: return False
        for i in range(m.length):
            if m.exponents.at(i) != self.exponents.at(i): return False
        return True

# This will only work in sage        
def listMonomials(degree, length):
    """List all Monomials of a given degree"""
    return [Monomial (length, v) for v in IntegerVectors(degree, length).list()]

def listDivisibleMonomials (degree, m, length):
    """ List all monomials of given degree that are divisible by m"""
    remainingDegree = degree - m.degree()
    mi = m.invert()
    return [n.divide(mi) for n in listMonomials(remainingDegree, length)]

