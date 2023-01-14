//
// Created by Ksenob1te on 29.11.2022.
//

#include "gameBalance.h"
#include "math.h"
#include "classes_header/array.h"

unsigned ll combinations(size_t n, size_t k) {
    if ((n - k) > k) k = n - k;
    ll top = 1, bottom = 1;
    for (int i = 1; i <= n; ++i) {
        if (i > k) top *= i;
        if (i <= (n - k)) bottom *= i;
    }
    return top / bottom;
}

void toBinaryArray(unsigned int *maskElement, unsigned ll bit, size_t len, int element) {
    len--;
    while (bit) {
        if (bit % 2)
            maskElement[len] = element;
        len--;
        bit /= 2;
    }
}


unsigned ll maxBit(unsigned int bits) {
    unsigned ll v = 1;
    for (int i = 0; i < bits; ++i)
        v *= 2;
    v -= 1;
    return v;
}

void sameBitCountGenerator(unsigned ll *array, unsigned int bits, const size_t *maskSize) {
    unsigned ll v = maxBit(bits);

    for (int i = 0; i < *maskSize; ++i) {
        array[i] = v;
        unsigned ll t = (v | (v - 1)) + 1;
        v = t | ((((t & -t) / (v & -v)) >> 1) - 1);
    }
}

unsigned int **createTeamMasks(const size_t *teamSize, size_t *maskSize) {
    *maskSize = combinations(*teamSize * 2, *teamSize) / 2;
    unsigned int **teamMask = malloc(*maskSize * sizeof(unsigned int *));
    unsigned ll teamBits[*maskSize];
    sameBitCountGenerator(teamBits, *teamSize, maskSize);
    for (ll i = 0; i < *maskSize; ++i) {
        teamMask[i] = calloc(*teamSize * 2, sizeof(unsigned int));
        toBinaryArray(teamMask[i], teamBits[i], *teamSize * 2, 1);
    }
    return teamMask;
}

unsigned int **createRoleMasks(const size_t *teamSize, size_t *maskSize, int tankPlayers, int dpsPlayers) {
    size_t tMaskSize = combinations(*teamSize, tankPlayers);
    unsigned ll tankBits[tMaskSize];
    sameBitCountGenerator(tankBits, tankPlayers, &tMaskSize);
    size_t mMaskSize = combinations(*teamSize, tankPlayers + dpsPlayers);
    unsigned ll mainBits[mMaskSize * sizeof(unsigned int)];
    sameBitCountGenerator(mainBits, tankPlayers + dpsPlayers, &mMaskSize);
    size_t counter = 0;
    *maskSize = mMaskSize * combinations(tankPlayers + dpsPlayers, tankPlayers);
    unsigned int **ansArray = malloc(*maskSize * sizeof(unsigned int *));
    unsigned int mb = maxBit(*teamSize);
    for (int i = 0; i < mMaskSize; ++i) {
        for (int j = 0; j < tMaskSize; ++j) {
            if ((mainBits[i] & tankBits[j]) == tankBits[j]) {
                ansArray[counter] = calloc(*teamSize, sizeof(unsigned int));
                toBinaryArray(ansArray[counter], mainBits[i] & (-tankBits[j] - 1), *teamSize, 1);
                toBinaryArray(ansArray[counter], (-mainBits[i] - 1) & mb, *teamSize, 2);
                counter++;
            }
        }
    }
    *maskSize = counter;
    return ansArray;
}

bool checkRoleMask(const unsigned int *roleMask, const struct Player *team, const size_t *teamSize) {
    bool res = true;
    for (int i = 0; i < *teamSize; ++i)
        if (!team[i].checkIndex(team + i, roleMask[i])) res = false;
    return res;
}

void checkMask(
        struct Results currentArray, size_t *resultsSize,
        const unsigned int *teamMask,
        const unsigned int **roleMasks, const size_t *masksSize,
        const struct Player *players, const size_t *teamSize) {
    struct Player *fTeam = malloc(*teamSize * sizeof(struct Player)),
            *sTeam = malloc(*teamSize * sizeof(struct Player));
    int fTeamCounter = 0, sTeamCounter = 0;
    for (int i = 0; i < *teamSize * 2; ++i) {
        if (teamMask[i] == 0) fTeam[fTeamCounter++] = players[i];
        else sTeam[sTeamCounter++] = players[i];
    }
    for (int i = 0; i < *masksSize; ++i) {
        const unsigned int * fMask = roleMasks[i];
        if (checkRoleMask(roleMasks[i], fTeam, teamSize))
            for (int j = 0; j < *masksSize; ++j) {
                const unsigned int * sMask = roleMasks[j];
                if (checkRoleMask(roleMasks[j], sTeam, ))

            }
    }


}

struct Balance *createGame(char **pUsernames, int *pPTS, int *pFlex, char **pRoles, size_t teamSize) {

}

