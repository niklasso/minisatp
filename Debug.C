#include "Debug.h"


vec<cchar*>* debug_names = NULL;

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void dump(Int num) {
    if      (num == Int_MIN) reportf("-oo");
    else if (num == Int_MAX) reportf("+oo");
    else                     { char* tmp = toString(num); reportf("%s", tmp); xfree(tmp); } }


void dump(Lit p) {
    if (debug_names == NULL)
        reportf("%sx%d", sign(p)?"~":"", var(p));
    else{
        if (var(p) < debug_names->size())
            reportf("%s%s", sign(p)?"~":"", (*debug_names)[var(p)]);
        else
            reportf("%s@%d", sign(p)?"~":"", var(p));
    }
}


void dump(Formula f) {
    if (Atom_p(f))
        reportf("%sv%d", sign(f)?"~":"", index(f));
    else
        reportf("%s@%d", sign(f)?"~":"", index(f));
}


void dump(const vec<Lit>& ps, const vec<Int>& Cs)
{
    assert(ps.size() == Cs.size());
    for (int i = 0; i < ps.size(); i++){
        dump(Cs[i]);
        reportf("*");
        dump(ps[i]);
        if (i+1 < ps.size()) reportf("  ");
    }
}

void dump(const vec<Formula>& ps, const vec<Int>& Cs)
{
    assert(ps.size() == Cs.size());
    for (int i = 0; i < ps.size(); i++){
        dump(Cs[i]);
        reportf("*");
        dump(ps[i]);
        if (i+1 < ps.size()) reportf("  ");
    }
}


void dump(const vec<Lit>& ps, const vec<Int>& Cs, const vec<int>& assigns)
{
    assert(ps.size() == Cs.size());
    for (int i = 0; i < ps.size(); i++){
        dump(Cs[i]);
        reportf("*");
        dump(ps[i]);
        if (assigns[var(ps[i])] == toInt(l_Undef))
            reportf(":?");
        else if ((assigns[var(ps[i])] == toInt(l_True) && !sign(ps[i])) || (assigns[var(ps[i])] == toInt(l_False) && sign(ps[i])))
            reportf(":1");
        else
            reportf(":0");
        if (i+1 < ps.size()) reportf("  ");
    }
}


void dump(const Linear& pb)
{
    for (int i = 0; i < pb.size; i++){
        dump(pb(i));
        reportf("*");
        dump(pb[i]);
        reportf("  ");
    }
    reportf("in ["); dump(pb.lo); reportf(","); dump(pb.hi); reportf("]");
}


void dump(const Linear& pb, const vec<int>& assigns)
{
    for (int i = 0; i < pb.size; i++){
        dump(pb(i));
        reportf("*");
        dump(pb[i]);
        if (assigns[var(pb[i])] == toInt(l_Undef))
            reportf(":?");
        else if ((assigns[var(pb[i])] == toInt(l_True) && !sign(pb[i])) || (assigns[var(pb[i])] == toInt(l_False) && sign(pb[i])))
            reportf(":1");
        else
            reportf(":0");
        if (i+1 < pb.size) reportf("  ");
    }
    reportf("in ["); dump(pb.lo); reportf(","); dump(pb.hi); reportf("]");
}
