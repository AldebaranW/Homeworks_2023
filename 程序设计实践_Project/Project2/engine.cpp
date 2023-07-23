//
// Created by Wu on 2023/6/20.
//

#include "engine.h"

Engine::Engine(std::vector<int> cmd, int enemy_type)
{   
    assert((int)cmd.size() == 3);
    player = new Player(cmd[0], cmd[1], cmd[2]);
    switch (enemy_type) {
    case 1:
        enemy = new Sunny_Enemy();
    }
}

// The main fuction to process the gameplay
void Engine::Play()
{
    this->Begin(); // Beginning process

    int end = 0;
    int round = 1;

    while (!end && round <= 100) {
        std::cout << "Round " << round << std::endl;

        // Select Action
        int action = 0, cmd = 0;
        Action player_act; 
        do {
            std::cout << "Select your action (0 for escape, 1 for skill" << (player->pet_remain > 1 ? ", 2 for change):" : "):") << std::endl;
            std::cin >> action;
            if (action < 1 || action > 2) 
                action = 0;
            if (player->pet_remain == 1 && action != 1)
                action = 0;
        } while (action == 0);

        player_act.type = ActionType(action - 1);
        player_act.is_player = 1;
        switch (action) {
        case 1:
            while (cmd < 1 || cmd > 2) {
                std::cout << "Select the skill (1 for Tackle, 2 for " << player->GetPetOnStage().GetSkills()[2].name << "):";
                std::cin >> cmd;
                player_act.power = 20;
                player_act.atk = player->GetPetOnStage().GetAttackPoints();
                player_act.property = player->GetPetOnStage().GetSkills()[cmd].property;
                player_act.priority = 0;
                player_act.index = player->GetPetOnStageIndex();
            }
            break;
        case 2:
            std::vector<int> aval;
            for (int i = 0; i < 3; ++i) {
                if (i == player->GetPetOnStageIndex())
                    continue;
                aval.push_back(i);
            }
            std::cout << "Select your next pet (";
            bool comma = 0;
            for (int a : aval) {
                std::cout << (int)comma + 1 << " for " << player->GetPets()[a].GetName();
                if (!comma) {
                    std::cout << ", ";
                    comma = 1;
                }
            }
            std::cout << "):";
            std::cin >> cmd;
            player_act.index = aval[cmd - 1];
            player_act.priority = 6;
        }

        // Execute Action && Change
        Action enemy_act = enemy->MakeAction(player); // Get the enemy's move

        int player_first = 0; // Record whether player or enemy goes first
        if (player_act.priority > enemy_act.priority) {
            player_first = 1;
        } else if (player_act.priority < enemy_act.priority) {
            player_first = 0;
        } else {
            if (player->GetPetOnStage().GetVelocity() > enemy->GetPetOnStage().GetVelocity()) {
                player_first = 1;
            } else {
                player_first = 0;
            }
        }

        // Process the action of two players
        if (player_first) {
            std::pair<int, int> tmp = this->ProcessAct(player_act, player, enemy);
            int skip = tmp.first, end = tmp.second;

            if (end) {
                EndGame(1);
                return;
            }

            if (!skip)
                end = this->ProcessAct(enemy_act, enemy, player).second;

            if (end) {
                EndGame(0);
                return;
            }
        } else {
            std::pair<int, int> tmp = this->ProcessAct(enemy_act, enemy, player);
            int skip = tmp.first, end = tmp.second;

            if (end) {
                EndGame(0);
                return;
            }

            if (!skip)
                end = this->ProcessAct(player_act, player, enemy).second;

            if (end) {
                EndGame(1);
                return;
            }
        }

        EndRound();
        if (round == 100) {
            std::cout << "Draw" << std::endl;
            return;
        }
        round++;
    }
}

/*
    This function process the action made by player1

    Which player is the aim of the action depends on the type of the action, as the CHANGE and POTION process aims at the player1 himself and ATTACK aims at the other

    The procession on the ATTACK also includes the passive pet-changing part and judging whether the game reaches an end
*/
std::pair<int, int> Engine::ProcessAct(Action act, Player* player1, Player* player2)
{
    int skip = 0;
    int end = 0;
    if (act.type != ATTACK) {
        player1->ProcessAction(act);
    } else {
        std::pair<int, int> tmp = player2->ProcessAction(act);
        int change_flag = tmp.first;
        int end_flag = tmp.second;

        if (end_flag) {
            std::cout << (!player2->player_type ? "Your " : "Enemy's ") << player2->GetPetOnStage().GetName() << " is beaten" << std::endl;

            return std::make_pair(1, 1);
        }

        if (change_flag) {
            skip = 1;
            std::cout << (!player2->player_type ? "Your " : "Enemy's ")
                      << player2->GetPetOnStage().GetName() << " is beaten" << std::endl;
            int index = 0;
            if (player2->player_type) {
                index = (player1->GetPetOnStageIndex() + 1) % 3;
            } else {
                std::vector<int> aval;
                int cmd = 0;
                for (int i = 0; i < 3; ++i) {
                    if (player->GetPets()[i].GetHP() <= 0)
                        continue;
                    aval.push_back(i);
                }
                while (cmd < 1 || cmd > aval.size()) {
                    std::cout << "Select your next pet (";
                    bool comma = 0;
                    for (int i = 0; i < aval.size(); ++i) {
                        std::cout << (int)comma + 1 << " for " << player->GetPets()[aval[i]].GetName();
                        if (!comma && aval.size() == 2) {
                            std::cout << ", ";
                            comma = 1;
                        }
                    }
                    std::cout << "):";
                    std::cin >> cmd;
                }
                index = aval[cmd - 1];
            }
            player2->ChangePet(index);
        }
    }
    return std::make_pair(skip, end);
}

void Engine::Begin()
{
    std::cout << "You start with " << player->GetPetOnStage().GetName() << std::endl;
    std::cout << "Enemy starts with " << enemy->GetPetOnStage().GetName() << std::endl;
    std::cout << "Your " << player->GetPetOnStage().GetName() << ": HP " << player->GetPetOnStage().GetHP();
    std::cout << " || ";
    std::cout << "Enemy's " << enemy->GetPetOnStage().GetName() << ": HP " << enemy->GetPetOnStage().GetHP() << std::endl;
    std::cout << "Battle starts!" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;
}

void Engine::EndRound()
{
    std::cout << "Your " << player->GetPetOnStage().GetName() << ": HP " << player->GetPetOnStage().GetHP();
    std::cout << " || ";
    std::cout << "Enemy's " << enemy->GetPetOnStage().GetName() << ": HP " << enemy->GetPetOnStage().GetHP() << std::endl;
}

void Engine::EndGame(bool is_player)
{
    if (is_player) {
        std::cout << "You Win" << std::endl;
    } else {
        std::cout << "You Lose" << std::endl;
    }
}