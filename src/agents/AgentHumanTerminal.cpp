// AgentHumanTerminal.h

#include <cstdint>
#include <iostream>
#include <regex>

#include "agents/AgentHumanTerminal.h"

uint64_t AgentHumanTerminal::get_move(const Board &board)
{
    static std::regex pattern("^[a-h][1-8]$");

    uint64_t int_move;

    while (true)
    {
        std::cout << "Input: ";

        std::string str_move;
        std::cin >> str_move;

        if (!(std::regex_match(str_move, pattern)))
        {
            std::cout << "Expected <letter><number>. Try again." << std::endl;
            continue;
        }

        char file = str_move[0];
        char rank = str_move[1];

        int col = file - 'a';
        int row = rank - '1';

        int bit_index = row * 8 + col;
        int_move = 1ULL << bit_index;

        if (!(int_move & board.legal))
        {
            std::cout << "Not a legal move. Try again." << std::endl;
            continue;
        }
        break;
    }

    return int_move;
}
