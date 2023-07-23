#include <iostream>
#include "engine.h"

int main() {
    std::cout << "Welcome to Battle of Pets!\n"
                "You have W, L and G. So does Enemy." << std::endl;

    int initial_pet = 0;
    while (initial_pet < 1 || initial_pet > 3) {
        std::cout << "Select your starting pet (1 for W, 2 for L, 3 for G):" ;
        std::cin >> initial_pet;
    }

    // Create the engine to lauch the game
    Engine engine(initial_pet - 1, 0);
    engine.Play();

    return 0;
}
