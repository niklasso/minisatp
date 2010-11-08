#include "PbSolver.h"
#include "Hardware.h"

//-------------------------------------------------------------------------------------------------
void    linearAddition (const Linear& c, vec<Formula>& out);        // From: PbSolver_convertAdd.C
Formula buildConstraint(const Linear& c, int max_cost = INT_MAX);   // From: PbSolver_convertSort.C
Formula convertToBdd   (const Linear& c, int max_cost = INT_MAX);   // From: PbSolver_convertBdd.C
//-------------------------------------------------------------------------------------------------


bool PbSolver::convertPbs(bool first_call)
{
    vec<Formula>    converted_constrs;

    if (first_call){
        findIntervals();
        if (!rewriteAlmostClauses()){
            ok = false;
            return false; }
    }

    for (int i = 0; i < constrs.size(); i++){
        if (constrs[i] == NULL) continue;
        Linear& c   = *constrs[i]; assert(c.lo != Int_MIN || c.hi != Int_MAX);

        if (opt_verbosity >= 1)
            /**/reportf("---[%4d]---> ", constrs.size() - 1 - i);

        if (opt_convert == ct_Sorters)
            converted_constrs.push(buildConstraint(c));
        else if (opt_convert == ct_Adders)
            linearAddition(c, converted_constrs);
        else if (opt_convert == ct_BDDs)
            converted_constrs.push(convertToBdd(c));
        else if (opt_convert == ct_Mixed){
            int adder_cost = estimatedAdderCost(c);
            //**/printf("estimatedAdderCost: %d\n", estimatedAdderCost(c));
            Formula result = convertToBdd(c, (int)(adder_cost * opt_bdd_thres));
            if (result == _undef_)
                result = buildConstraint(c, (int)(adder_cost * opt_sort_thres));
            if (result == _undef_)
                linearAddition(c, converted_constrs);
            else
                converted_constrs.push(result);
        }else
            assert(false);

        if (!ok) return false;
    }

    constrs.clear();
    mem.clear();

    clausify(sat_solver, converted_constrs);

    return ok;
}
