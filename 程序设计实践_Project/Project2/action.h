//
// Created by Wu on 2023/6/25.
//

#ifndef PROJECT1_ACTION_H
#define PROJECT1_ACTION_H

#include <iostream>
#include "pet.h"



struct Action {
    bool is_player;
    int priority;
    ActionType type;
    std::string name;
};


#endif //PROJECT1_ACTION_H
