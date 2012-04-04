"""
Try to find a witness for a Markov move (with parallelization)
"""

# combinations_with_replacement will be available in Python 2.7
# from itertools import combinations_with_replacement as cwr

def combinations_with_replacement(items, n):
    if n==0: yield []
    else:
        for i in xrange(len(items)):
            for ss in combinations_with_replacement(items, n-1):
                yield [items[i]]+ss


from searching import *
from monomial import *

def createVar (i,n):
    l = [0 for j in range(n)]
    l[i]=1
    return Monomial(n, l)

class NoWitnessFound (Exception):
    pass

class WitnessSearch:
    def __init__(self, nvars, moves, markovElement, numjobs=4, Verbose=False):
        self.nvars=nvars
        self.moves=moves
        self.markovElement=markovElement
        self.verbose=Verbose
        self.numjobs=numjobs
                
    def findWitness(self, stoppingDegree=False):
        """ Stopping degree is the last degree of potential witnesses that will be checked"""
        d = 1;
        variables=[createVar(i,self.nvars) for i in range(self.nvars)]
        while (stoppingDegree == False or (d <= stoppingDegree)):
            todo = combinations_with_replacement(variables, d)
            for t in todo:
                m=Monomial(self.nvars, [0 for jj in range (self.nvars)])
                for tt in t: m = m.multiply(tt)
                if self.verbose:
                    print "Now testing:"
                    print m
                mp = self.markovElement.positivePart().multiply(m)
                mn = self.markovElement.negativePart().multiply(m)
                if inSameComponent(mp, mn, self.moves, Verbose=self.verbose):
                    if self.verbose: print "Witness found!"
                    return m
            d = d+1
        print "No witness found"
        raise NoWitnessFound

    
