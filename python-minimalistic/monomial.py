"""
A monomial is a minimalistic data structure consisting of an exponent vector.
At some point we may even switch to some smaller self-managed binary coding,
but int will do for now.

Monomials are implemented almost immutable.  We can set their exponents, but
otherwise all operations create new monomials.
"""

from sage.all import IntegerVectors

class LengthMismatch (Exception):
    """Exception to indicate that a given exponent vector does not fit this
    monomial"""
    pass

class NotApplicable (Exception):
    pass

class monomial(object):
    def __init__(self, length, exponents=None):
        """The length is mandatory to create the data structure"""
        self.length=length
        if exponents:
            self.exponents=exponents
        else:
            self.exponents=[0 for l in range(length)]

    def __str__ (self):
         return str(self.exponents)
    
    def set(self, exponents):
        if len(exponents)==length:
            self.exponents=exponents
        else:
            raise LengthMismatch()

    def invert(self):
        return monomial(self.length, [-i for i in self.exponents])

    def isDivisible (self, m):
        if len(exponents)==length:
            for i in range(length):
                if self.exponents[i] < m.exponents[i]:
                    return False
            return True
        else:
            raise LengthMismatch()

    def multiply (self, m):
        if m.length==self.length:
            return monomial(self.length, [self.exponents[i] + m.exponents[i] for i in range (self.length)])
        else:
            raise LengthMismatch()

    def divide (self, m):
        if m.length==self.length:
            return monomial(self.length, [self.exponents[i] - m.exponents[i] for i in range (self.length)])
        else:
            raise LengthMismatch()

    def positivePart (self):
        return monomial (self.length, [max(self.exponents[i], 0) for i in range (self.length)])

    def negativePart (self):
        return monomial (self.length, [max(-self.exponents[i], 0) for i in range (self.length)])

    def degree (self):
        return sum (self.exponents)

    def applyBinomial(self, b):
        raise NotImplementedError()

    def applyBinomialSafe (self,b):
        if self.length != b.length: raise LengthMismatch()
        resultExponents = [0 for i in range (self.length)]
        for i in range (self.length):
            if self.exponents[i] < b.exponents[i]: raise NotApplicable()
            resultExponents[i] = self.exponents[i] - b.exponents[i]
        return monomial(self.length, resultExponents)

    def isProper (self):
        return isDivisible(monomial(length))

    # Todo, implement proper comparison operator
    def isSame (self,m):
        if not m.length == self.length: return False
        for i in range(m.length):
            if m.exponents[i] != self.exponents[i]: return False
        return True


# This will only work in sage        
def listMonomials(degree, length):
    """List all monomials of a given degree"""
    return [monomial (length, v) for v in IntegerVectors(degree, length).list()]

def listDivisibleMonomials (degree, m, length):
    """ List all monomials of given degree that are divisible by m"""
    remainingDegree = degree - m.degree()
    mi = m.invert()
    return [n.divide(mi) for n in listMonomials(remainingDegree, length)]

