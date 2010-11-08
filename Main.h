#ifndef Main_h
#define Main_h

#include "Int.h"

//=================================================================================================


enum SolverT  { st_MiniSat, st_SatELite };
enum ConvertT { ct_Sorters, ct_Adders, ct_BDDs, ct_Mixed, ct_Undef };
enum Command  { cmd_Minimize, cmd_FirstSolution, cmd_AllSolutions };

// -- output options:
extern bool     opt_satlive;
extern bool     opt_ansi;
extern char*    opt_cnf;
extern int      opt_verbosity;
extern bool     opt_try;

// -- solver options:
extern SolverT  opt_solver;
extern ConvertT opt_convert;
extern ConvertT opt_convert_goal;
extern bool     opt_convert_weak;
extern double   opt_bdd_thres;
extern double   opt_sort_thres;
extern double   opt_goal_bias;
extern Int      opt_goal;
extern Command  opt_command;
extern bool     opt_branch_pbvars;
extern int      opt_polarity_sug;

// -- files:
extern char*    opt_input;
extern char*    opt_result;

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void reportf(const char* format, ...);      // 'printf()' replacer -- will put "c " first at each line if 'opt_satlive' is TRUE.


//=================================================================================================
#endif
