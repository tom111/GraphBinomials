# Simple tasks:
# 1) Enumrate all monomials of a given degree
A.<x,y,z> = QQ[]
degree=3
exponents = IntegerVectors(A.ngens(),degree).list()
def toMonomial (expo):
    return prod ([A.gen(i)^expo[i] for i in range (A.ngens())])
monomials = [toMonomial (e) for e in exponents]

# Upshot: Maybe define a class 'monomial'?

# 2) Define the graph with vertices the monomials and edges the binomials

from sage.graphs.graph import Graph

class GraphOnMonomials (Graph):
    True;
    

# 3) Search the connected components

# Abstraction of Data structures
