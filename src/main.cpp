// main.cpp
// Entry point for command-line-interface (CLI) version of Reversi

#include <iostream>
#include "core/GameManager.h"

int main(int argc, char **argv)
{
    // --- Cmdline Args ---
    if (argc != 3)
    {
        std::cerr << "[USAGE] ./main <player1type> <player2type>\n"
                  << "  0 = human terminal\n"
                  << "  1 = random bot\n"
                  << "  2 = minimax bot\n"
                  << std::endl;
        return 1;
    }

    // --- Game Setup ---
    int p1_type = std::atoi(argv[1]);
    int p2_type = std::atoi(argv[2]);

    // --- Game Run ---
    GameManager game(p1_type, p2_type);
    game.run();

    return 0;
}
