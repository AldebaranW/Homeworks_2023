//
// Created by Wu on 2023/6/20.
//

#ifndef PROJECT1_PET_H
#define PROJECT1_PET_H

#include "algorithm"
#include "map"
#include "vector"
#include <iostream>
#include "utils.h"

class Pet {
public:
    Pet(int index);
    std::string GetName();
    Property GetProperty();
    int GetHP();
    int GetFullHP();
    int GetAttackPoints();
    int GetVelocity();

    bool IsAlive();
    bool IsPoitioned();
    bool IsPainted();
    bool IsAsleep();
    Skill GetSkills(int index);
    std::pair<int, int> ProcessAttack(Property property, int power, int atk);
    void ProcessPoition(int poition_type);

protected:
    std::string name;
    Property property;
    int max_hp;
    int atk;
    int def;
    int spd;
    std::vector<Skill> skills;

    int hp;
    int is_poitioned = 0;
    int is_painted = 0;
    int is_asleep = 0;
};

extern std::vector<std::string> pet_name;
extern std::vector<int> pet_hp;

#endif // PROJECT1_PET_H
