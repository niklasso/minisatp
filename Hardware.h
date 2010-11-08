#ifndef Hardware_h
#define Hardware_h

#include "FEnv.h"
#include "PbSolver.h"

//=================================================================================================


int  estimatedAdderCost(const Linear& c);
void oddEvenSort(vec<Formula>& fs);
void rippleAdder(const vec<Formula>& xs, const vec<Formula>& ys, vec<Formula>& out);
void addPb(const vec<Formula>& ps, const vec<Int>& Cs_, vec<Formula>& out, int bits);

void clausify(Solver& s, const vec<Formula>& fs, vec<Lit>& out);
void clausify(Solver& s, const vec<Formula>& fs);


//=================================================================================================
#endif
