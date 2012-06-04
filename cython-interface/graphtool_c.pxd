cdef extern from "../graphbinomial.h":
    void printMessage()
    bool inSameComponent (const Monomial& m1, const Monomial& m2, const vector<Binomial>& moves)

cdef extern from "../monomial.h":
    cdef cppclass Monomial:
        long length
        std::vector<int> *exponents
        Monomial (long llength)
        Monomial (long llength, const std::vector<int>& exponents)
        Monomial (const std::vector<int>& expo)
        Monomial (const Monomial& m)
        ~Monomial ()
        std::string toString () const
        Monomial* inverse () const
        bool isDivisible (const Monomial& m) const
        long degree() const
        bool operator== (const Monomial& m) const
        Monomial* applyBinomialSafe (const Binomial& b) const
        Monomial* applyBinomialSafeReverse (const Binomial& b) const
        bool isProper () const

cdef extern from "../binomial.h":
    cdef cppclass Binomial:
        Monomial *head
        Monomial *tail
        Binomial (const std::vector<int>& exponents)
        Binomial (const std::vector<int>& headExp, const std::vector<int>& tailExp)
        Binomial (const Monomial& hd, const Monomial& tl)
        Binomial (const Binomial& b)
        ~Binomial ()
    

