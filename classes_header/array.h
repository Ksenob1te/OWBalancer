//
// Created by Ksenob1te on 30.11.2022.
//

#ifndef OWBALANCER_ARRAY_H
#define OWBALANCER_ARRAY_H
#include "stdlib.h"
#include "../classes_header/const.h"

struct Results {
    int *fRoleMask;
    int *sRoleMask;
    int *teamMask;
    size_t teamSize;
    ldb result, uniformity, fairness;
    struct Results *next;
}; extern const struct ResultsClass {
    struct Results (*new)(int *fRoleMask, int *sRoleMask, int*teamMask, size_t teamSize,
            ldb result, ldb uniformity, ldb fairness);
} Results;

static struct Results newResults(int *fRoleMask, int *sRoleMask, int*teamMask, size_t teamSize,
                                 ldb result, ldb uniformity, ldb fairness);



#endif //OWBALANCER_ARRAY_H
