//
// Created by Wu on 2023/6/25.
//

#ifndef PROJECT1_ACTION_H
#define PROJECT1_ACTION_H

#include <iostream>
#include "pet.h"

enum ActionType {ATTACK, CHANGE, POTION};

struct Action {
    bool is_player;
    int priority;
    ActionType type;
    Property property;
    int power;
    int attack_pt;
    int index;
};


#endif //PROJECT1_ACTION_H
