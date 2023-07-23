//
// Created by Wu on 2023/6/20.
//

#ifndef PROJECT1_PLAYER_H
#define PROJECT1_PLAYER_H
#include "pet.h"
#include "action.h"

class Player {
public:
    Player(int initial_pet);

    Pet& GetPetOnStage();
    int GetPetOnStageIndex();
    std::vector<Pet>& GetPets();

    virtual std::pair<int, int> ProcessAction(Action& action);
    virtual void ChangePet(int index/* 1, 2, 3 */);

    int player_type;
    int pet_remain;
protected:
    int pet_on_stage = -1; // 0, 1, 2
    std::vector<Pet> pets = {Pet(1), Pet(2), Pet(3)};
    
};

#endif //PROJECT1_PLAYER_H
