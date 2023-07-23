//
// Created by Wu on 2023/6/20.
//

#include "pet.h"

std::vector<std::string> pet_name = { "W", "L", "G", "Q", "D" };
std::vector<int> pet_hp = { 110, 100, 100, 90, 120 };
std::vector<int> pet_atk = { 10, 12, 10, 10, 9 };
std::vector<int> pet_def = { 10, 10, 14, 10, 8 };
std::vector<int> pet_spd = { 10, 11, 9, 12, 7 };

std::vector<std::vector<Skill>> pet_skill = {
    { skill_dict["Tackle"], skill_dict["Leaf"], skill_dict["Synthesis"] },
    { skill_dict["Claw"], skill_dict["Flame"], skill_dict["Sunny"] },
    { skill_dict["Tackle"], skill_dict["Stream"], skill_dict["Rainy"] },
    { skill_dict["Quick"], skill_dict["Volt"], skill_dict["Thunder"] },
    { skill_dict["Slap"], skill_dict["Sing"], skill_dict["Paint"] }
};

Pet::Pet(int index)
{
    this->property = Property(index);
    this->name = pet_name[index];
    this->max_hp = pet_hp[index];
    this->atk = pet_atk[index];
    this->def = pet_def[index];
    this->spd = pet_spd[index];
    this->skills = pet_skill[index];

    this->hp = this->max_hp;
}

std::string Pet::GetName()
{
    return this->name;
}

Property Pet::GetProperty()
{
    return this->property;
}

int Pet::GetHP()
{
    return this->hp;
}

int Pet::GetFullHP()
{
    return this->max_hp;
}

int Pet::GetAttackPoints()
{
    return this->atk;
}

int Pet::GetVelocity()
{
    return this->spd;
}

bool Pet::IsAlive() {
    return this->hp > 0;
}

bool Pet::IsPoitioned()
{
    return this->is_poitioned;
}

bool Pet::IsPainted()
{
    return this->IsPainted();
}

bool Pet::IsAsleep()
{
    return this->is_asleep;
}

Skill Pet::GetSkills(int index)
{
    return this->skills[index];
}

std::pair<int, int> Pet::ProcessAttack(Property property, int power, int atk)
{
    float float_final_power = (float)power * (float)atk / (float)this->def * property_bonus[property][this->property];
    int final_power = (int)(float_final_power + 0.5);
    this->hp -= final_power;
    if (this->hp <= 0) {
        this->is_poitioned = 0;
        this->atk /= 2;
        return std::make_pair(0, final_power);
    }
    return std::make_pair(1, final_power);
}

void Pet::ProcessPoition(int poition_type)
{
    switch (poition_type) {
    case 1:
        this->hp = this->max_hp / 2;
        this->is_poitioned = 0;
        break;
    case 2:
        this->atk *= 2;
        this->is_poitioned = 1;
        break;
    }
}