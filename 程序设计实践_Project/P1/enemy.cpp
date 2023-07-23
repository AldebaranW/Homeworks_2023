//
// Created by Wu on 2023/6/20.
//

#include "enemy.h"

Enemy::Enemy(int initial_pet) : Player(initial_pet) {
    this->pet_on_stage = (initial_pet + 1) % 3;
    this->player_type = 1;
}

/*
    The basic complementation of the action of the enemy

    A dictionary is used to judge whether the pet is facing a pet of its weakness
*/
Action Enemy::MakeAction(Player* player)
{
    Action action;
    action.is_player = 0;
    action.priority = 0;
    action.type = ATTACK;
    action.attack_pt = this->GetPetOnStage().GetAttackPoints();
    action.index = this->GetPetOnStageIndex();

    if (property_bonus[this->GetPetOnStage().GetProperty()][player->GetPetOnStage().GetProperty()] > 1) {
        action.property = this->GetPetOnStage().GetSkills()[2].property;
        action.power = this->GetPetOnStage().GetSkills()[2].power;
    } else {
        action.property = this->GetPetOnStage().GetSkills()[1].property;
        action.power = this->GetPetOnStage().GetSkills()[1].power;
    }

    return action;
}

void Enemy::ChangePet(int index)
{
    if (this->GetPets()[index].GetHP() > 0) {
        Player::ChangePet(index);
    } else if (this->GetPets()[(index - 1) % 3].GetHP() > 0) {
        Player::ChangePet((index - 1) % 3);
    } else {
        Player::ChangePet(index % 3);
    }

}

Greedy_Enemy::Greedy_Enemy(int initial_pet)
    : Enemy(initial_pet)
{
    this->player_type = 2;
}

/*
    The complementation of the greedy_enemy's action logic
*/
Action Greedy_Enemy::MakeAction(Player* player)
{
    Action action;
    action.is_player = 0;

    if (this->pet_remain == 1) {
        action = Enemy::MakeAction(player);
        return action;
    }

    // 如果有克制的pet则换上
    if (this->pets[(player->GetPetOnStageIndex() + 1) % 3].GetHP() > 0 && (player->GetPetOnStageIndex() + 1) % 3 != this->GetPetOnStageIndex()) {
        action.type = CHANGE;
        action.priority = 6;
        action.index = (player->GetPetOnStageIndex() + 1) % 3;
        return action;
    }

    // 如果没有克制的pet且场上pet被克制则换下
    if (property_bonus[player->GetPetOnStage().GetProperty()][this->GetPetOnStage().GetProperty()] > 1) {
        action.type = CHANGE;
        action.priority = 6;
        action.index = player->GetPetOnStageIndex();
        return action;
    }

    action = Enemy::MakeAction(player);
    return action;
}

Potion_Enemy::Potion_Enemy(int initial_pet)
    : Greedy_Enemy(initial_pet)
{
    this->player_type = 3;
}

Action Potion_Enemy::MakeAction(Player* player)
{
    Action action;
    action.is_player = 0;

    if (this->revival_poition == 1 && this->pet_remain != 3) {
        action.type = POTION;
        action.priority = 5;
        action.index = 1;
        for (int i = 0; i < 3; ++i) {
            if (this->GetPets()[i].GetHP() <= 0) {
                action.power = i;
                break;
            }
        }
        return action;
    }

    if (!this->GetPetOnStage().IsPoitioned() && this->attack_poition != 0 && property_bonus[player->GetPetOnStage().GetProperty()][this->GetPetOnStage().GetProperty()] <= 1) {
        action.type = POTION;
        action.priority = 5;
        action.index = 2;
        return action;
    }

    if (this->GetPetOnStage().IsPoitioned()) {
        action = Enemy::MakeAction(player);
        return action;
    }

    // std::cout << "test" << std::endl;

    action = Greedy_Enemy::MakeAction(player);
    return action;
}

std::pair<int, int> Potion_Enemy::ProcessAction(Action& action)
{
    if (action.type == POTION) {
        int change_flag = 0;
        int end_flag = 0;
        std::cout << "Enemy uses " << (action.index == 1 ? "Revival Potion" : "Attack Potion") << " on ";
        if (action.index == 1) {
            this->pet_remain ++;
            this->revival_poition -= 1;
            this->GetPets()[action.power].ProcessPoition(action.index);
            std::cout << this->GetPets()[action.power].GetName() << std::endl;
        } else {
            this->attack_poition -= 1;
            this->GetPetOnStage().ProcessPoition(action.index);
            std::cout << this->GetPetOnStage().GetName() << std::endl;
        }
        return std::make_pair(change_flag, end_flag);
    }

    return Player::ProcessAction(action);
}