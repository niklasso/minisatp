#ifndef PbParser_h
#define PbParser_h

#include "PbSolver.h"


//=================================================================================================


void parse_PB_file(cchar* filename, PbSolver& solver, bool abort_on_error = true);
void parse_PB     (cchar* text    , PbSolver& solver, bool abort_on_error = true);


//=================================================================================================
#endif
