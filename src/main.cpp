// Othello App
// main.cpp

#include <cstdint>  // for uint64_t. we could use unsigned int, but this is more specific
#include <iomanip>  // for std::hex
#include <iostream> // for std::cout std::cin std::endl std::cerr
#include <sstream>  // for parsing cmdline prompt
#include <vector>

#include "Board.hpp"
#include "GameManager.hpp"
#include "GameMode.hpp"

// main.cpp
int main(int argc, char **argv) {

    // Args
    if (argc != 2) {
        std::cout << "[USAGE] Expected game mode. ./main <mode>" << std::endl;
        return 1;
    }

    // Set Game Mode
    int game_mode = HUMAN_HUMAN;
    if (argc > 1) {
        char arg = argv[1][0]; // Take the first character
        switch (arg) {
            case '1':
                game_mode = HUMAN_BOT;
                break;
            case '2':
                game_mode = BOT_HUMAN;
                break;
            case '3':
                game_mode = BOT_BOT;
                break;
            default:
                break;
        }
    }

    // Spin up an instance of Othello and play!
    GameManager game;
    game.play_terminal_version(game_mode);

    return 0;
}
