//
// Created by Ksenob1te on 10.10.2022.
//

#ifndef OWBALANCER_PLAYER_H
#define OWBALANCER_PLAYER_H
#include "stdlib.h"
#include "../classes_header/const.h"
#include "../classes_header/role.h"

static int tagToIndex(char tag);
static char indexToTag(int index);

struct Player {
    char Roles[4];
    char* Username;
    bool flex;
    struct Role Tank, Dps, Heal;
    void (*activateIndexes) (struct Player* this, const int* indexes, size_t array_size);
    void (*activateTags) (struct Player* this, const char* tags, size_t array_size);
    bool (*checkIndex) (const struct Player* this, unsigned int index);
    bool (*checkTag) (struct Player* this, char tag);
    int (*countPriorityPoints) (const struct Player* this, int index);
    void (*changeFlex) (struct Player* this);
    int (*getIndexSR) (const struct Player* this, int index);
}; extern const struct PlayerClass {
    struct Player (*new)(int TSR, int DSR, int HSR, char* Username);
} Player;

static void activateIndexes(struct Player* this, const int* indexes, size_t array_size);
static void activateTags(struct Player* this, const char* tags, size_t array_size);
static bool checkPlayerIndex(const struct Player* this, unsigned int index);
static bool checkPlayerTag(struct Player* this, char tag);
static int countPriorityPoints(const struct Player* this, int index);
static void changeFlex(struct Player* this);
static int getIndexSR(const struct Player* this, int index);
static struct Player newPlayer(int TSR, int DSR, int HSR, char* Username);

#endif //OWBALANCER_PLAYER_H
