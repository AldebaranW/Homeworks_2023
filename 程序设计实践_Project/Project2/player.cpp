//
// Created by Wu on 2023/6/20.
//

#include "player.h"

Player::Player(int pet1, int pet2, int pet3)
    : pet_remain(3)
    , player_type(0)
    , pets({ Pet(pet1), Pet(pet2), Pet(pet3) })
    , pet_on_stage(0) {};

Pet& Player::GetPetOnStage()
{
    return this->pets[pet_on_stage];
}

int Player::GetPetIndexByName(std::string name)
{
    for (int i = 0; i < (int)this->pets.size(); ++i) {
        if (pets[i].GetName() == name) {
            return i;
        }
    }

    return -1;
}

std::string Player::GetPetNameByIndex(int index)
{
    return this->pets[index].GetName();
}

Pet& Player::GetPetByIndex(int index)
{
    return this->pets[index];
}

std::vector<Pet>& Player::GetPets()
{
    return this->pets;
}

Pet& Player::GetPetByName(std::string name)
{
    return this->pets[this->GetPetIndexByName(name)];
}

void Player::MakeAttack(Action& action, int index)
{
    assert(index >= 0 && index < 3);
    action.is_player = 1;
    action.type = ATTACK;
    action.name = this->GetPetOnStage().GetSkills(index).name;
    action.priority = this->GetPetOnStage().GetSkills(index).prio;
}

void Player::MakeChange(Action& action, int index)
{
    assert(index >= 0 && index < 3 && this->GetPetByIndex(index).IsAlive());
    action.is_player = 1;
    action.type = CHANGE;
    action.name = this->GetPetNameByIndex(index);
    action.priority = 6;
}

Action Player::MakeAction(Player* player, Weather weather)
{
    while (1) {
        Action player_act;
        int action = 0, cmd = -1;
        do {
            std::cout << "Select your action (0 for escape, 1 for skill" << (player->pet_remain > 1 ? ", 2 for change):" : "):") << std::endl;
            std::cin >> action;
            if (action < 1 || action > 2)
                action = 0;
            else if (player->pet_remain == 1 && action != 1)
                action = 0;
        } while (action == 0);

        switch (action) {
        case 0:
            player_act.type = ESCAPE;
            return player_act;
        case 1:
            while (cmd < 0) {
                std::cout << "Select the skill (0 for back, 1 for " << this->GetPetOnStage().GetSkills(0).name << ", 2 for " << this->GetPetOnStage().GetSkills(1).name << ", 3 for " << this->GetPetOnStage().GetSkills(2).name << "):";
                std::cin >> cmd;
                if (cmd < 0 || cmd > 3)
                    cmd = -1;
            }
            if (!cmd)
                continue;
            break;
        case 2:
            std::vector<int> aval;
            for (int i = 0; i < 3; ++i) {
                if (i == this->GetPetOnStageIndex())
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
    }
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
    std::string prompt = "";
    switch (action.type) {
    case CHANGE: {
        std::cout << this->ChangePet(action.index) << std::endl;
        break;
    }
    case ATTACK: {
        prompt += (player_type ? "Your " : "Enemy's ");
        prompt += this->GetPetOnStage().GetName();
        prompt += " uses ";
        prompt += this->GetPetOnStage().GetSkills()[action.property].name;
        prompt += "! Damage: ";

        std::pair<int, int> tmp = this->GetPetOnStage().ProcessAttack(action.property, action.power, action.atk);

        prompt += std::to_string(tmp.second);

        change_flag = !tmp.first;
        if (change_flag)
            this->pet_remain -= 1;
        if (!this->pet_remain) {
            end_flag = 1;
        }

        std::cout << prompt << std::endl;
        break;
    }
    default:
        throw "Player: Invalid action";
        break;
    }

    return std::make_pair(change_flag, end_flag);
}

std::string Player::ChangePet(int index)
{
    std::string prompt;
    prompt = (!player_type ? "You send " : "Enemy sends ");
    prompt += this->GetPetOnStage().GetName();
    this->pet_on_stage = index;
    return prompt;
}