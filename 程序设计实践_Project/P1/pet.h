//
// Created by Wu on 2023/6/20.
//

#ifndef PROJECT1_PET_H
#define PROJECT1_PET_H

#include <iostream>
#include "map"
#include "vector"
#include "algorithm"

enum Property {NORMAL, GRASS, FIRE, WATER};
enum SkillType {POWER, ASSIST};

struct  Skill {
    std::string name;
    Property property;
    SkillType type;
    int power = 20;
    int prio;
    Skill() = default;
    Skill(Property prop); // For Project 1
    Skill(std::string name, Property property, SkillType type, int power, int prio); // For Project 2
};

extern std::map<int, std::string> pet_type;
extern std::map<Property, std::string> skill_names;
extern std::map<std::string, Skill> skill_dict;
extern std::vector<std::vector<float>> property_bonus;

class Pet {
public:
    Pet(int index);
    std::string  GetName();
    Property GetProperty();
    int GetHP();
    int GetAttackPoints();
    int GetVelocity();
    bool IsPoitioned();
    std::map<int, Skill> GetSkills();
    std::pair<int, int> ProcessAttack(Property property, int power, int
    attack_pt);
    void ProcessPoition(int poition_type);
protected:
    std::string name;
    Property property;
    int max_hp;
    int attack_pt;
    int deffense_pt;
    int vel;
    std::map<int, Skill> skills;

    int hp;
    int is_poitioned = 0;
};


#endif //PROJECT1_PET_H
