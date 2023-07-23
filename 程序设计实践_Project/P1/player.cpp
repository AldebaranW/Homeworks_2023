//
// Created by Wu on 2023/6/20.
//

#include "player.h"

Player::Player(int initial_pet)
    : pet_remain(3)
{
    this->player_type = 0;
    this->pet_on_stage = initial_pet;
}

Pet& Player::GetPetOnStage()
{
    return this->pets[pet_on_stage];
}

int Player::GetPetOnStageIndex()
{
    return this->pet_on_stage;
}

std::vector<Pet>& Player::GetPets()
{
    return this->pets;
}

/*
    The fuction to process one action

    if action.type is CHANGE, then the player changes the pet on the field
    if action.type is ATTACK, then the player process the attack from the rival's pet
    
    the procession of using the POTION is complemented in the Class Enemy's overloaded function
*/
std::pair<int, int> Player::ProcessAction(Action& action)
{
    int change_flag = 0;
    int end_flag = 0;
    switch (action.type) {
    case CHANGE: {
        this->ChangePet(action.index);
        break;
    }
    case ATTACK: {
        std::cout << (player_type ? "Your " : "Enemy's ");
        std::cout << pet_type[action.index + 1] << " uses " << skill_names[action.property] << "! Damage: ";
        std::pair<int, int> tmp = this->GetPetOnStage().ProcessAttack(action.property, action.power, action.attack_pt);
        change_flag = !tmp.first;
        if (change_flag)
            this->pet_remain -= 1;
        if (this->pet_remain == 0) {
            end_flag = 1;
        }
        int final_power = tmp.second;
        std::cout << final_power << std::endl;
        break;
    }
    default:
        break;
    }
    return std::make_pair(change_flag, end_flag);
}

void Player::ChangePet(int index)
{
    this->pet_on_stage = index;
    std::cout << (!player_type ? "You send " : "Enemy sends ");
    std::cout << this->GetPetOnStage().GetName() << std::endl;
}