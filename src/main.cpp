// Othello App
// main.cpp

#include <iostream> // for std::cout std::cin std::endl std::cerr
#include <iomanip>  // for std::hex
#include <sstream>  // for parsing cmdline prompt
#include <cstdint>  // for uint64_t. we could use unsigned int, but this is more specific
#include <vector> 

#include "GameManager.hpp"
#include "Board.hpp"

// main.cpp

enum GameMode : int {
    HUMAN_HUMAN = 0,
    HUMAN_BOT = 1,
    BOT_HUMAN =2,
    BOT_BOT = 3
};

int main()
{
    std::cout << "Welcome to Othello! \n";

    GameManager game(HUMAN_HUMAN);
    game.play_terminal_version();

    return 0;
}

