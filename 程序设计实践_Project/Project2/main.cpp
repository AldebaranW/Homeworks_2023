#include "engine.h"
#include <iostream>

std::vector<int> Begin(int enemy_type);

int main()
{
    std::vector<int> cmd = Begin(1);

    // Create the engine to lauch the game
    Engine engine(cmd, 1);
    engine.Play();

    return 0;
}

std::vector<int> Begin(int enemy_type)
{
    std::vector<int> cmd;
    std::cout << "Welcome to Battle of Pets 2!" << std::endl;
    if (enemy_type == 1)
        std::cout << "Enemy has D, W and L." << std::endl;
    else
        std::cout << "Enemy has W, G and Q." << std::endl;
    std::cout << "You can select three from five (1 for W, 2 for L, 3 for G, 4 for Q, 5 for D)." << std::endl;
    for (int i = 0; i < 3; i++) {
        int select = -1;
        while (select < 0) {
            std::cout << "Select your " << i + 1 << (!i ? "st" : (i == 1 ? "nd" : "rd")) << " pet: ";
            std::cin >> select;
            if (select < 1 || select > 5)
                select = -1;
        }
        cmd.push_back(select - 1);
    }

    std::cout << "You have " << pet_name[cmd[0]] << ", " << pet_name[cmd[1]] << " and " << pet_name[cmd[2]] << "." << std::endl;
    return cmd;
}