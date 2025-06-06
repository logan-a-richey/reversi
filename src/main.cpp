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

int set_mode(char arg) {
    switch (arg) {
        case '1':
            return HUMAN_BOT;
            break;
        case '2':
            return BOT_HUMAN;
            break;
        case '3':
            return BOT_BOT;
            break;
        default:
            return HUMAN_HUMAN;
    }
}

// main.cpp
int main(int argc, char **argv) {
    int game_mode = HUMAN_HUMAN;

    // specific terminal usage of the game: $ ./main <mode>
    if (argc >= 2) {
        char arg = argv[1][0];
        game_mode = set_mode(arg);
    }

    // Spin up an instance of Othello and play!
    GameManager game;
    game.play_terminal_version(game_mode);

    return 0;
}
