//
// Created by Ksenob1te on 29.11.2022.
//

#ifndef OWBALANCER_GAMEBALANCE_H
#define OWBALANCER_GAMEBALANCE_H
#include "stdlib.h"
#include "classes_header/balance.h"
#include "classes_header/player.h"

unsigned ll combinations(size_t n, size_t k);
unsigned int ** createTeamMasks(const size_t * teamSize, size_t * maskSize);
unsigned int ** createRoleMasks(const size_t * teamSize, size_t * maskSize, int tankPlayers, int dpsPlayers);
void sameBitCountGenerator(unsigned ll *array, unsigned int bits, const size_t *maskSize);
unsigned ll maxBit(unsigned int bits);
void toBinaryArray(unsigned int *maskElement, unsigned ll bit, size_t len, int element);

#endif //OWBALANCER_GAMEBALANCE_H
