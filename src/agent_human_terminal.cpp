// agent_human_terminal.cpp

#include "agent_human_terminal.h"

#include <iostream>
#include <string>
// #include <regex>
#include "board.h"
#include "move.h"

Move AgentHumanTerminal::get_move(const Board &board) {
    while (true) {
        std::cout << "Input: ";

        std::string str_move;
        std::cin >> str_move;

        bool is_legal_move = false;
        for (const auto &move : board.legal_moves) {
            if (str_move == move.symbol) {
                is_legal_move = true;
                return move;
            }
        }

        if (!is_legal_move) {
            std::cout << "Invalid or illegal move. Try again." << std::endl;
        }
    }
}
