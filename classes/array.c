//
// Created by Ksenob1te on 30.11.2022.
//
#include "../classes_header/array.h"

const struct ResultsClass Results={.new=&newResults};

static struct Results newResults(int *fRoleMask, int *sRoleMask, int*teamMask, size_t teamSize,
                                 ldb result, ldb uniformity, ldb fairness) {
    return (struct Results) {
            .fRoleMask=fRoleMask,
            .sRoleMask=sRoleMask,
            .teamMask=teamMask,
            .teamSize=teamSize,
            .result=result,
            .uniformity=uniformity,
            .fairness=fairness,
            .next=NULL
    };
}
