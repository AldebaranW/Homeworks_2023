//
// Created by Wu on 2023/6/20.
//

#include "pet.h"
std::map<int, std::string> pet_type = { std::make_pair(1, "W"), std::make_pair(2, "L"), std::make_pair(3, "G") };
std::map<Property, std::string> skill_names = { std::make_pair(NORMAL,
                                                    "Tackle"),
    std::make_pair(GRASS, "Leaf"),
    std::make_pair(FIRE, "Flame"),
    std::make_pair(WATER, "Stream") };
std::map<std::string, Skill> skill_dict = {};
std::vector<std::vector<float>> property_bonus = { { 1, 1, 1, 1 },
    { 1, 0.5, 0.5, 2 },
    { 1, 2, 0.5, 0.5 },
    { 1, 0.5, 2, 0.5 } };

Skill::Skill(Property prop)
{
    property = prop;
    name = skill_names[prop];
}

Skill::Skill(std::string name, Property property, SkillType type, int power, int prio) : name(name), property(property), type(type), power(power), prio(prio){};

Pet::Pet(int index)
{
    this->property = Property(index);
    this->name = pet_type[index];
    this->max_hp = (index == 1) ? 110 : 100;
    this->attack_pt = (index == 2) ? 11 : 10;
    this->deffense_pt = (index == 3) ? 11 : 10;
    this->vel = (index == 1 ? 10 : (index == 2 ? 11 : 9));
    this->skills = { std::make_pair(1, Skill(Property(0))),
        std::make_pair(2, Skill(Property(index))) };

    this->hp = this->max_hp;
}

std::string Pet::GetName()
{
    return pet_type[this->property];
}

Property Pet::GetProperty()
{
    return this->property;
}

int Pet::GetHP()
{
    return this->hp;
}

int Pet::GetAttackPoints()
{
    return this->attack_pt;
}

int Pet::GetVelocity()
{
    return this->vel;
}

bool Pet::IsPoitioned()
{
    return this->is_poitioned;
}

std::map<int, Skill> Pet::GetSkills()
{
    return this->skills;
}

std::pair<int, int> Pet::ProcessAttack(Property property, int power, int attack_pt)
{
    float float_final_power = (float)power * (float)attack_pt / (float)this->deffense_pt * property_bonus[property][this->property];
    int final_power = (int)(float_final_power + 0.5);
    this->hp -= final_power;
    if (this->hp <= 0) {
        this->is_poitioned = 0;
        this->attack_pt /= 2;
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
        this->attack_pt *= 2;
        this->is_poitioned = 1;
        break;
    }
}