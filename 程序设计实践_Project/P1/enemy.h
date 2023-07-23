//
// Created by Wu on 2023/6/20.
//

#ifndef PROJECT1_ENEMY_H
#define PROJECT1_ENEMY_H
#include "action.h"
#include "player.h"

class Enemy : public Player {
public:
    Enemy(int initial_pet);
    virtual void ChangePet(int index) override;
    virtual Action MakeAction(Player* player);
};

class Greedy_Enemy : public Enemy {
public:
    Greedy_Enemy(int initial_pet);
    virtual Action MakeAction(Player* player) override;
};

class Potion_Enemy : public Greedy_Enemy {
public:
    Potion_Enemy(int initial_pet);
    virtual Action MakeAction(Player* player) override;
    std::pair<int, int> ProcessAction(Action& action) override;

protected:
    int revival_poition = 1;
    int attack_poition = 2;
};

#endif // PROJECT1_ENEMY_H
