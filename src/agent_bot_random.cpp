// agent_bot_random.cpp

#include "agent_bot_random.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include "board.h"

AgentBotRandom::AgentBotRandom() {
    // seed to current time
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

Move AgentBotRandom::get_move(const Board &board) {
    int num_moves = board.legal_moves.size();

    if (num_moves == 0) {
        // TODO - debug
        std::cerr << "[E] RandomBot has no legal moves available." << std::endl;
        exit(1);
    }

    unsigned int random_index = std::rand() % num_moves;
    return board.legal_moves[random_index];
}

