//
// Created by Ksenob1te on 10.11.2022.
//

#include "math.h"
#include "limits.h"
#include "../classes_header/player.h"
#include "../classes_header/balance.h"

const struct BalanceClass Balance={.new=&newBalance};

ldb dpFairness(const int *FT, const int *ST, const size_t team_size, const double p) {
    ldb ft_p = 0;
    for (int i = 0; i < team_size; i++)
        ft_p += pow(FT[i], p);
    ldb st_p = 0;
    for (int i = 0; i < team_size; i++)
        st_p += pow(ST[i], p);
    return fabsl(powl(ft_p, 1. / p) - powl(st_p, 1. / p));
}

ldb rgRolesFairness(
        const int *FT, const int *ST, const int *fMask, const int *sMask,
        const size_t team_size, const double g,
        const double tW, const double dW, const double hW) {
    int fRoles[3] = {0, 0, 0};
    int sRoles[3] = {0, 0, 0};
    for (int i = 0; i < team_size; i++)
        fRoles[fMask[i]] += FT[i];
    for (int i = 0; i < team_size; i++)
        sRoles[sMask[i]] += ST[i];
    return fabsl(
            powl(
                    (
                            pow(fabs((fRoles[0] - sRoles[0]) * tW), g) +
                            pow(fabs((fRoles[1] - sRoles[1]) * dW), g) +
                            pow(fabs((fRoles[2] - sRoles[2]) * hW), g)
                    ) / 3,
                    1. / g
            )
    );
}

ldb vqUniformity(const int* FT, const int* ST, const size_t team_size, const double q) {
    double muz = 0;
    for (int i = 0; i < team_size; i++)
        muz += FT[i] + ST[i];
    muz /= ((int)team_size * 2.);
    ldb ft_p = 0;
    for (int i = 0; i < team_size; i++)
        ft_p += powl(fabs(FT[i] - muz), q);
    ft_p /= team_size;
    ldb st_p = 0;
    for (int i = 0; i < team_size; i++)
        st_p += powl(fabs(ST[i] - muz), q);
    st_p /= team_size;
    return fabsl(powl(ft_p, 1. / q) - powl(st_p, 1. / q));
}

ldb teamRolesPriority(
        const struct Player* fPlayers, const struct Player* sPlayers,
        const size_t team_size, const int* fMask, const int* sMask) {
    ldb points = (int) team_size * 2 * 3;
    int fTPoints = (int) team_size * 3;
    int sTPoints = (int) team_size * 3;
    for (int i = 0, role = fMask[i]; i < team_size; i++, role = fMask[i]) {
        int sub = fPlayers[i].countPriorityPoints(&fPlayers[i], role);
        fTPoints -= sub;
        points -= sub;
    }
    for (int i = 0, role = sMask[i]; i < team_size; i++, role = sMask[i]) {
        int sub = sPlayers[i].countPriorityPoints(&sPlayers[i], role);
        sTPoints -= sub;
        points -= sub;
    }
    if (abs(fTPoints - sTPoints) > 1)
        points = 0.2 * (abs(fTPoints - sTPoints));
    return points;
}


void imbalanceFunc(struct Balance* this) {
    double tWeight = 1.1, dWeight = 1.0, hWeight = 0.7,
            alpha = 5.0, beta = 1.0, gamma = 60.0, p = 2.0, q = 2.0;

    int ftPts[this->team_size], stPts[this->team_size];
    for (int i = 0, role = this->fMask[i]; i < this->team_size; ++i, role = this->fMask[i])
        ftPts[i] = this->fTeam[i].getIndexSR(&(this->fTeam[i]), role);
    for (int i = 0, role = this->sMask[i]; i < this->team_size; ++i, role = this->sMask[i])
        stPts[i] = this->sTeam[i].getIndexSR(&(this->sTeam[i]), role);

    this->dpF = alpha * dpFairness(ftPts, stPts, this->team_size, p);
    this->rgR = beta * rgRolesFairness(ftPts, stPts, this->fMask, this->sMask, this->team_size, p, tWeight, dWeight, hWeight);
    this->trP = gamma * teamRolesPriority(this->fTeam, this->sTeam, this->team_size, this->fMask, this->sMask);
    this->vqU = vqUniformity(ftPts, stPts, this->team_size, q);
    this->result = this->dpF + this->rgR + this->trP + this->vqU;
}

void clearBalance(struct Balance* this) {}

static struct Balance newBalance(const struct Player* fTeam, const struct Player* sTeam,
                                 int* fMask, int* sMask, const int* teamMask, size_t team_size) {

    return (struct Balance) {
            .result=INT_MAX,
            .team_size=team_size,
            .vqU = 0, .trP = 0, .rgR=0, .dpF=0,
            .fTeam=fTeam, .sTeam=sTeam,
            .fMask=fMask, .sMask=sMask, .teamMask=teamMask,
            .clear=clearBalance,

            .imbalanceFunc=imbalanceFunc,
    };
}

