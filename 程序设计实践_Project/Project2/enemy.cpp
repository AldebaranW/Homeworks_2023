//
// Created by Wu on 2023/6/20.
//

#include "enemy.h"

/*
    The basic complementation of the action of the enemy

    A dictionary is used to judge whether the pet is facing a pet of its weakness
*/

// Greedy_Enemy::Greedy_Enemy(int initial_pet)
//     : Enemy(initial_pet)
// {
//     this->player_type = 2;
// }

/*
    The complementation of the greedy_enemy's action logic
*/
// Action Greedy_Enemy::MakeAction(Player* player)
// {
//     Action action;
//     action.is_player = 0;

//     if (this->pet_remain == 1) {
//         action = Enemy::MakeAction(player);
//         return action;
//     }

//     // 如果有克制的pet则换上
//     if (this->pets[(player->GetPetOnStageIndex() + 1) % 3].GetHP() > 0 && (player->GetPetOnStageIndex() + 1) % 3 != this->GetPetOnStageIndex()) {
//         action.type = CHANGE;
//         action.priority = 6;
//         action.index = (player->GetPetOnStageIndex() + 1) % 3;
//         return action;
//     }

//     // 如果没有克制的pet且场上pet被克制则换下
//     if (property_bonus[player->GetPetOnStage().GetProperty()][this->GetPetOnStage().GetProperty()] > 1) {
//         action.type = CHANGE;
//         action.priority = 6;
//         action.index = player->GetPetOnStageIndex();
//         return action;
//     }

//     action = Enemy::MakeAction(player);
//     return action;
// }

// Potion_Enemy::Potion_Enemy(int initial_pet)
//     : Greedy_Enemy(initial_pet)
// {
//     this->player_type = 3;
// }

// Action Potion_Enemy::MakeAction(Player* player)
// {
//     Action action;
//     action.is_player = 0;

//     if (this->revival_poition == 1 && this->pet_remain != 3) {
//         action.type = POTION;
//         action.priority = 5;
//         action.index = 1;
//         for (int i = 0; i < 3; ++i) {
//             if (this->GetPets()[i].GetHP() <= 0) {
//                 action.power = i;
//                 break;
//             }
//         }
//         return action;
//     }

//     if (!this->GetPetOnStage().IsPoitioned() && this->attack_poition != 0 && property_bonus[player->GetPetOnStage().GetProperty()][this->GetPetOnStage().GetProperty()] <= 1) {
//         action.type = POTION;
//         action.priority = 5;
//         action.index = 2;
//         return action;
//     }

//     if (this->GetPetOnStage().IsPoitioned()) {
//         action = Enemy::MakeAction(player);
//         return action;
//     }

//     // std::cout << "test" << std::endl;

//     action = Greedy_Enemy::MakeAction(player);
//     return action;
// }

// std::pair<int, int> Potion_Enemy::ProcessAction(Action& action)
// {
//     if (action.type == POTION) {
//         int change_flag = 0;
//         int end_flag = 0;
//         std::cout << "Enemy uses " << (action.index == 1 ? "Revival Potion" : "Attack Potion") << " on ";
//         if (action.index == 1) {
//             this->pet_remain ++;
//             this->revival_poition -= 1;
//             this->GetPets()[action.power].ProcessPoition(action.index);
//             std::cout << this->GetPets()[action.power].GetName() << std::endl;
//         } else {
//             this->attack_poition -= 1;
//             this->GetPetOnStage().ProcessPoition(action.index);
//             std::cout << this->GetPetOnStage().GetName() << std::endl;
//         }
//         return std::make_pair(change_flag, end_flag);
//     }

//     return Player::ProcessAction(action);
// }

Sunny_Enemy::Sunny_Enemy()
    : Player(4, 0, 1)
{
    this->player_type = 1;
}

void Sunny_Enemy::MakeAttack(Action& action, int index)
{   
    Player::MakeAttack(action, index);
    action.is_player = 0;
}

void Sunny_Enemy::MakeChange(Action& action, int index)
{
    Player::MakeChange(action, index);
    action.is_player = 0;
}

Action Sunny_Enemy::MakeAction(Player* player, Weather weather)
{
    Action action;
    Pet& p_pet = player->GetPetOnStage();
    Pet& my_pet = this->GetPetOnStage();

    if (my_pet.GetName() == "W" && my_pet.GetHP() < my_pet.GetFullHP() * 0.5 && this->GetPetByName("L").IsAlive()) {
        this->MakeChange(action, this->GetPetIndexByName("L"));

    } else if (my_pet.GetName() == "D") {
        float loss = (float)p_pet.GetHP() / p_pet.GetFullHP();
        bool painted = p_pet.IsPainted();
        bool asleep = p_pet.IsAsleep();

        if (loss < 1. / 3) {
            if (painted || asleep)
                this->MakeAttack(action, 0);
            else
                this->MakeAttack(action, 1);
        } else {
            if (!asleep)
                this->MakeAttack(action, 1);
            else if (!painted)
                this->MakeAttack(action, 2);
            else
                this->MakeAttack(action, 0);
        }

    } else if (my_pet.GetName() == "W") {
        float prop = (float)my_pet.GetHP() / my_pet.GetFullHP();

        if (prop >= 0.5 || (my_pet.GetHP() > p_pet.GetHP() && this->pet_remain == 1)) {
            if (p_pet.GetProperty() == WATER)
                this->MakeAttack(action, 1);
            else
                this->MakeAttack(action, 0);
        } else {
            this->MakeAttack(action, 2);
        }

    } else if (my_pet.GetName() == "L") {
        float loss = (float)p_pet.GetHP() / p_pet.GetFullHP();

        if (loss < 1. / 5 && (p_pet.GetProperty() == FIRE || p_pet.GetProperty() == WATER))
            this->MakeAttack(action, 0);
        else {
            if (weather == SUNNY)
                this->MakeAttack(action, 1);
            else
                this->MakeAttack(action, 2);
        }
    }

    return action;
}