"""
Try to find a witness for a Markov move (with parallelization)
"""

from itertools import combinations

from searching import *
from monomial import *

def createVar (i,n):
    l = [0 for j in range(n)]
    l[i]=1
    return monomial(n, l)

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
            todo = combinations(variables, d)
            for t in todo:
                m=monomial(self.nvars)
                for tt in t: m = m.multiply(tt)
                if self.verbose:
                    print "Now testing:"
                    print m
                mp = self.markovElement.positivePart().multiply(m)
                mn = self.markovElement.negativePart().multiply(m)
                if inSameComponent(mp, mn, self.moves, Verbose=self.verbose):
                    if self.Verbose: print "Witness found!"
                    return m
            d = d+1
        print "No witness found"
        raise NoWitnessFound

    
