/**************************************************************************************************

SolverTypes.h -- (C) Niklas Een, Niklas Sörensson, 2004

Contains the solver specific types: Var, Lit, Clause

**************************************************************************************************/


#ifndef SolverTypes_h
#define SolverTypes_h

#include "Int.h"


//=================================================================================================
// Variables, literals:


// NOTE! Variables are just integers. No abstraction here. They should be chosen from 0..N,
// so that they can be used as array indices.

typedef int Var;
#define var_Undef (-1)


class Lit {
    int     x;
public:
    Lit(void)   /* unspecifed value allowed for efficiency */      { }
    explicit Lit(Var var, bool sign = false) : x((var+var) + sign) { }
    friend Lit operator ~ (Lit p);

    friend bool sign (Lit p);
    friend int  var  (Lit p);
    friend int  index(Lit p);
    friend Lit  toLit(int i);

    friend bool operator == (Lit p, Lit q);
    friend bool operator <  (Lit p, Lit q);
};
inline Lit operator ~ (Lit p) { Lit q; q.x = p.x ^ 1; return q; }
inline bool sign (Lit p) { return p.x & 1; }
inline int  var  (Lit p) { return p.x >> 1; }
inline int  index(Lit p) { return p.x; }        // A "toInt" method that guarantees small, positive integers suitable for array indexing.
inline Lit  toLit(int i) { Lit p; p.x = i; return p; }
inline bool operator == (Lit p, Lit q) { return index(p) == index(q); }
inline bool operator <  (Lit p, Lit q) { return index(p)  < index(q); }  // '<' guarantees that p, ~p are adjacent in the ordering.

const Lit lit_Undef(var_Undef, false);  // }- Useful special constants.
const Lit lit_Error(var_Undef, true );  // }

macro uint64 abstLit(Lit p) { return ((uint64)1) << (index(p) & 63); }

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#define L_LIT    "%sx%d"
#define L_lit(p) sign(p)?"~":"", var(p)

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

struct BasicSolverStats {
    int64   starts, decisions, propagations, inspects, conflicts;
    BasicSolverStats(void) : starts(0), decisions(0), propagations(0), inspects(0), conflicts(0) { }
};

//=================================================================================================
#endif
