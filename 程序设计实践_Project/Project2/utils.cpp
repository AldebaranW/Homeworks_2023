#include "utils.h"

std::map<std::string, Skill> skill_dict = {
    std::make_pair("Tackle", Skill("Tackle", NORMAL, ATK, 20, 0)),
    std::make_pair("Claw", Skill("Claw", NORMAL, ATK, 15, 0)),
    std::make_pair("Quick", Skill("Quick", NORMAL, ATK, 15, 1)),
    std::make_pair("Slap", Skill("Slap", NORMAL, ATK, 15, 0)),
    std::make_pair("Sing", Skill("Sing", NORMAL, ASS, 3, 0)),
    std::make_pair("Paint", Skill("Paint", NORMAL, ASS, 0, 0)),
    std::make_pair("Leaf", Skill("Leaf", GRASS, ATK, 20, 0)),
    std::make_pair("Synthesis", Skill("Synthesis", GRASS, ASS, 30, 0)),
    std::make_pair("Flame", Skill("Flame", FIRE, ATK, 20, 0)),
    std::make_pair("Sunny", Skill("Sunny", FIRE, ASS, 5, 1)),
    std::make_pair("Stream", Skill("Stream", WATER, ATK, 20, 0)),
    std::make_pair("Rainy", Skill("Rainy", WATER, ASS, 5, 1)),
    std::make_pair("Volt", Skill("Volt", ELECTRIC, ATK, 25, 0)),
    std::make_pair("Thunder", Skill("Thunder", ELECTRIC, ATK, 50, 0))
};

std::vector<std::vector<float>>
    property_bonus = { { 1, 1, 1, 1 }, { 1, 0.5, 0.5, 2 }, { 1, 2, 0.5, 0.5 }, { 1, 0.5, 2, 0.5 } };

Skill::Skill(std::string name, Property property, SkillType type, int power, int prio)
    : name(name)
    , property(property)
    , type(type)
    , power(power)
    , prio(prio) {};