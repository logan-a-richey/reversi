// AgentRandomBot.cpp

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include "Board.h"
#include "AgentRandomBot.h"

AgentRandomBot::AgentRandomBot()
{
    // Seed random to current time
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

uint64_t AgentRandomBot::get_move(const Board& board)
{
    std::vector<uint64_t> moves;

    for (int i = 1; i < 64; ++i)
    {
        if (1ULL << i & board.legal) moves.push_back(1ULL << i);
    }
    if (moves.empty())
    {
        std::cerr << "RandomBot has no legal moves available." << std::endl;
        return 0ULL;
    }
    
    unsigned int random_index = std::rand() % moves.size();
    return moves[random_index];
}
