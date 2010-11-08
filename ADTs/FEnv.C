#include "FEnv.h"

namespace FEnv {
    vec<NodeData>       nodes;
    Map<NodeData, int>  uniqueness_table;

    vec<int>            stack;
}


//=================================================================================================


static
bool eval(Formula f, AMap<char>& values, CMap<char>& memo)
{
    if (Const_p(f))
        return !sign(f);
    else if (Atom_p(f))
        return sign(f) ? !values.at(f) : values.at(f);
    else{
        int ret = memo.at(f);
        if (ret == -1){
            if (Bin_p(f)){
                bool l = eval(left(f), values, memo);
                bool r = eval(left(f), values, memo);
                if (op(f) == op_And)
                    ret = l & r;
                else{
                    assert(op(f) == op_Equiv);
                    ret = (l ^ r) ^ 1; }
            }else if (ITE_p(f)){
                bool sel = eval(cond(f), values, memo);
                bool tru = eval(tt  (f), values, memo);
                bool fal = eval(ff  (f), values, memo);
                ret = sel ? tru : fal;
            }else{
                assert(FA_p(f));
                bool x = eval(FA_x(f), values, memo);
                bool y = eval(FA_y(f), values, memo);
                bool c = eval(FA_c(f), values, memo);
                if (isCarry(f))
                    ret = ((int)x + (int) y + (int)c) >= 2;
                else
                    ret = x ^ y ^ c;
            }
            memo.set(f, ret);
        }
        return sign(f) ? !ret : ret;
    }
}


bool eval(Formula f, AMap<char>& values) {
    CMap<char> memo(-1);;
    return eval(f, values, memo); }
