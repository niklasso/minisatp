#ifndef DebugSolver_h
#define DebugSolver_h

//=================================================================================================


struct DebugSolver {
    int     c;
    DebugSolver() : c(0) {}
    lbool   value(Lit p) { return (var(p) != 0) ? l_Undef : (sign(p) ? l_False : l_True); }     // 'x0' is True, everything else undefined
    bool    addClause(vec<Lit>& lits) { printf("Added: {"); for (int i = 0; i < lits.size(); i++) printf(" %sx%d", sign(lits[i])?"~":"", var(lits[i])); printf(" }\n");  return true; }
    Var     newVar() { return c++; }
};

#define Solver DebugSolver


//=================================================================================================
#endif
