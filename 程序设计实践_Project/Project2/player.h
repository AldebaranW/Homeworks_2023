//
// Created by Wu on 2023/6/20.
//

#ifndef PROJECT1_PLAYER_H
#define PROJECT1_PLAYER_H
#include "pet.h"
#include "action.h"

class Player {
public:
    Player(int pet1, int pet2, int pet3);

    Pet& GetPetOnStage();
    int GetPetIndexByName(std::string name);
    std::string GetPetNameByIndex(int index);
    Pet& GetPetByIndex(int index);
    Pet& GetPetByName(std::string name);

    std::vector<Pet>& GetPets();

    virtual Action MakeAction(Player* player, Weather weather);
    virtual void MakeAttack(Action& action, int index);
    virtual void MakeChange(Action& action, int index);
    virtual std::pair<int, int> ProcessAction(Action& action);
    std::string ChangePet(int index/* 1, 2, 3 */);

    int player_type;
    int pet_remain;
protected:
    int pet_on_stage = -1; // 0, 1, 2
    std::vector<Pet> pets;
};

#endif //PROJECT1_PLAYER_H
