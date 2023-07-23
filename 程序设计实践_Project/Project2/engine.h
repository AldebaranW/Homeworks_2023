//
// Created by Wu on 2023/6/20.
//

#ifndef PROJECT1_ENGINE_H
#define PROJECT1_ENGINE_H

#include <iostream>
#include "player.h"
#include "enemy.h"
#include "action.h"

class Engine {
public:
    Engine(std::vector<int> cmd, int enemy_type);
    void Play();
private:
    Player* player;
    Player* enemy;
    Weather weather;

    void Begin();
    std::pair<int, int> ProcessAct(Action act, Player* player1, Player* player2);
    void EndRound();
    void EndGame(bool is_player);
};


#endif //PROJECT1_ENGINE_H
