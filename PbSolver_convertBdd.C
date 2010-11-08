#include "PbSolver.h"
#include "FEnv.h"
#include "Debug.h"


//=================================================================================================


static
//Formula buildBDD(const Linear& c, int size, int lower_limit, int upper_limit, int material_left, Map<Pair<int,Int>,Formula>& memo, int max_cost)
Formula buildBDD(const Linear& c, int size, Int sum, Int material_left, Map<Pair<int,Int>,Formula>& memo, int max_cost)
{
    Int lower_limit = (c.lo == Int_MIN) ? Int_MIN : c.lo - sum;
    Int upper_limit = (c.hi == Int_MAX) ? Int_MAX : c.hi - sum;

    if (lower_limit <= 0 && upper_limit >= material_left)
        return _1_;
    else if (lower_limit > material_left || upper_limit < 0)
        return _0_;
    else if (FEnv::topSize() > max_cost)
        return _undef_;     // (mycket elegant!)

    Pair<int,Int>   key = Pair_new(size, lower_limit);
    Formula         ret;

    if (!memo.peek(key, ret)){
        assert(size != 0);
        size--;
        material_left -= c(size);
        Int hi_sum = sign(c[size]) ? sum : sum + c(size);
        Int lo_sum = sign(c[size]) ? sum + c(size) : sum;
        Formula hi = buildBDD(c, size, hi_sum, material_left, memo, max_cost);
        if (hi == _undef_) return _undef_;
        Formula lo = buildBDD(c, size, lo_sum, material_left, memo, max_cost);
        if (lo == _undef_) return _undef_;
        ret = ITE(var(var(c[size])), hi, lo);
        memo.set(key, ret);
    }
    return ret;
}


// New school: Use the new 'ITE' construction of the formula environment 'FEnv'.
//
Formula convertToBdd(const Linear& c, int max_cost)
{
    Map<Pair<int,Int>, Formula> memo;

    Int sum = 0;
    for (int j = 0; j < c.size; j++)
        sum += c(j);

    FEnv::push();
    Formula ret = buildBDD(c, c.size, 0, sum, memo, max_cost);
    if (ret == _undef_)
        FEnv::pop();
    else{
        if (opt_verbosity >= 1)
            reportf("BDD-cost:%5d\n", FEnv::topSize());
        FEnv::keep();
    }
    return ret;
}
