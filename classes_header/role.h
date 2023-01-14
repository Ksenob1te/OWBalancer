//
// Created by Ksenob1te on 10.10.2022.
//

#ifndef OWBALANCER_ROLE_H
#define OWBALANCER_ROLE_H
#include "../classes_header/const.h"

struct Role {
    int SR, index;
    char tag;
    bool active;
    void (*activate)(struct Role* this);
    bool (*checkTag)(struct Role* this, char tag);
    bool (*checkIndex)(struct Role* this, int index);
};
extern const struct RoleClass {
    struct Role (*new)(int SR, char tag, int index);
} Role;

static void activate(struct Role* this);
static bool checkTag(struct Role* this, char tag);
static bool checkIndex(struct Role* this, int index);
static struct Role newRole(int SR, char tag, int index);

#endif //OWBALANCER_ROLE_H
