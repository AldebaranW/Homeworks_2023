#ifndef PROJECT1_SKILL_H
#define PROJECT1_SKILL_H

#include "algorithm"
#include "map"
#include "vector"
#include <cassert>
#include <iostream>

enum Property { GRASS,
    FIRE,
    WATER,
    ELECTRIC,
    NORMAL };
enum SkillType { ATK,
    ASS };
enum ActionType { ATTACK,
    CHANGE,
    POTION,
    ESCAPE };
enum Weather {
    FINE,
    SUNNY,
    RAINY
};

struct Skill {
    std::string name;
    Property property;
    SkillType type;
    int power = 20;
    int prio = 0;

    Skill() = default;
    Skill(Property prop); // For Project 1
    Skill(std::string name, Property property, SkillType type, int power, int prio); // For Project 2
};

extern std::map<std::string, Skill> skill_dict;
extern std::vector<std::vector<float>> property_bonus;

#endif