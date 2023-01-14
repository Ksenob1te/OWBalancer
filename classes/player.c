//
// Created by Ksenob1te on 10.11.2022.
//

#include "../classes_header/player.h"
#include "math.h"

static int tagToIndex(const char tag) {
    switch (tag) {
        case 'T': return 0;
        case 'D': return 1;
        case 'H': return 2;
        default: return -1;
    }
}
static char indexToTag(const int index) {
    switch (index) {
        case 0: return 'T';
        case 1: return 'D';
        case 2: return 'H';
        default: return '\0';
    }
}

const struct PlayerClass Player={.new=&newPlayer};

static void activateIndexes(struct Player* this, const int* indexes, size_t array_size) {
    for (int i = 0; i < 3; i++) {
        if (array_size - i > 0)
            this->Roles[i] = indexToTag(indexes[i]);
        else
            this->Roles[i] = '\0';
    }
    for (int i = 0; i < array_size; ++i) {
        if (this->Tank.index == indexes[i]) this->Tank.activate(&this->Tank);
        if (this->Dps.index == indexes[i]) this->Dps.activate(&this->Dps);
        if (this->Heal.index == indexes[i]) this->Heal.activate(&this->Heal);
    }
}
static void activateTags(struct Player* this, const char* tags, size_t array_size) {
    for (int i = 0; i < 3; i++) {
        if (array_size - i > 0)
            this->Roles[i] = tags[i];
        else
            this->Roles[i] = '\0';
    }
    for (int i = 0; i < array_size; ++i) {
        if (this->Tank.tag == tags[i]) this->Tank.activate(&this->Tank);
        if (this->Dps.tag == tags[i]) this->Dps.activate(&this->Dps);
        if (this->Heal.tag == tags[i]) this->Heal.activate(&this->Heal);
    }
}
static bool checkPlayerIndex(const struct Player* this, unsigned int index) {
    if (this->flex) return true;
    if (this->Tank.index == index) return this->Tank.active;
    if (this->Dps.index == index) return this->Dps.active;
    if (this->Heal.index == index) return this->Heal.active;
    return false;
}
static bool checkPlayerTag(struct Player* this, const char tag) {
    if (this->Tank.tag == tag) return this->Tank.active;
    if (this->Dps.tag == tag) return this->Dps.active;
    if (this->Heal.tag == tag) return this->Heal.active;
    return false;
}
static int countPriorityPoints(const struct Player* this, const int index) {
    if (this->flex) return 3;
    for (int i = 0; i <= 3; ++i) {
        if (this->Roles[i] == '\0') break;
        if (tagToIndex(this->Roles[i]) == index) return (3 - i);
    }
    return 0;
}
static void changeFlex(struct Player* this) {
    this->flex = !this->flex;
}
static int getIndexSR(const struct Player* this, const int index) {
    if (this->checkIndex(this, index)) {
        if (this->Tank.index == index) return this->Tank.SR;
        if (this->Dps.index == index) return this->Dps.SR;
        if (this->Heal.index == index) return this->Heal.SR;
    }
    return 0;
}
static struct Player newPlayer(int TSR, int DSR, int HSR, char* Username) {
    return (struct Player) {
            .Tank=Role.new(TSR, 'T', 0), .Dps=Role.new(DSR, 'D', 1), .Heal=Role.new(HSR, 'H', 2), .Username=Username,
            .flex = false, .Roles = "",

            .activateTags=activateTags,
            .activateIndexes=activateIndexes,
            .checkIndex=checkPlayerIndex,
            .checkTag=checkPlayerTag,
            .countPriorityPoints=countPriorityPoints,
            .changeFlex=changeFlex,
            .getIndexSR=getIndexSR
    };
}

