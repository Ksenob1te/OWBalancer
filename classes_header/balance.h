//
// Created by Ksenob1te on 01.11.2022.
//
#ifndef OWBALANCER_BALANCE_H
#define OWBALANCER_BALANCE_H
#include "../classes_header/const.h"

struct Balance {
    ldb result;
    size_t team_size;
    ldb dpF, rgR, trP, vqU;
    int *fMask;
    int *sMask;
    const int *teamMask;
    const struct Player* fTeam;
    const struct Player* sTeam;
    void (*imbalanceFunc) (struct Balance* this);
    void (*clear) (struct Balance* this);
}; extern const struct BalanceClass {
    struct Balance (*new)(const struct Player* fTeam, const struct Player* sTeam,
                          const int* fMask, const int* sMask, const int* teamMask, size_t team_size);
} Balance;

ldb dpFairness(const int *FT, const int *ST, size_t team_size, double p);
ldb rgRolesFairness(
        const int *FT, const int *ST, const int *fMask, const int *sMask,
        size_t team_size, double g,
        double tW, double dW, double hW);
ldb vqUniformity(const int* FT, const int* ST, size_t team_size, double q);
ldb teamRolesPriority(
        const struct Player* fPlayers, const struct Player* sPlayers,
        size_t team_size, const int* fMask, const int* sMask);
void clearBalance(struct Balance* this);

void imbalanceFunc(struct Balance* this);

static struct Balance newBalance(const struct Player* fTeam, const struct Player* sTeam,
        int* fMask, int* sMask, const int* teamMask, size_t team_size);

#endif //OWBALANCER_BALANCE_H
