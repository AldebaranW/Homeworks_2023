//
// Created by Wu on 2023/6/20.
//

#ifndef PROJECT1_ENEMY_H
#define PROJECT1_ENEMY_H
#include "action.h"
#include "player.h"


// class Greedy_Enemy : public Enemy {
// public:
//     Greedy_Enemy(int initial_pet);
//     virtual Action MakeAction(Player* player, Weather weather) override;
// };

// class Potion_Enemy : public Greedy_Enemy {
// public:
//     Potion_Enemy(int initial_pet);
//     virtual Action MakeAction(Player* player, Weather weather) override;
//     std::pair<int, int> ProcessAction(Action& action) override;

// protected:
//     int revival_poition = 1;
//     int attack_poition = 2;
// };

class Sunny_Enemy : public Player {
public:
    Sunny_Enemy();
    virtual Action MakeAction(Player* player, Weather weather) override;
protected:
    virtual void MakeAttack(Action& action, int index) override;
    virtual void MakeChange(Action& action, int index) override;
};

#endif // PROJECT1_ENEMY_H
