//
// Created by Ksenob1te on 10.11.2022.
//
#include "../classes_header/role.h"
const struct RoleClass Role={.new=&newRole};

static struct Role newRole(int SR, char tag, int index) {
    return (struct Role){.SR=SR, .tag=tag, .index=index, .active=false,
            .activate=activate, .checkTag=checkTag, .checkIndex=checkIndex};
}

static bool checkIndex(struct Role* this, int index) {return (this->index==index) ? true:false;}

static void activate(struct Role* this) {this->active = true;}

static bool checkTag(struct Role* this, char tag) {return (this->tag==tag) ? true:false;}