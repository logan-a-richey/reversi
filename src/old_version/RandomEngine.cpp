// RandomEngine.cpp

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include "Board.hpp"
#include "RandomEngine.hpp"

RandomEngine::RandomEngine()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

uint64_t RandomEngine::get_move(const Board &board)
{
    std::vector<uint64_t> moves;

    uint64_t compare = 1ULL << 63;
    while (compare)
    {
        if (compare & board.legal)
        {
            moves.push_back(compare);
        }
        compare >>= 1;
    }

    if (moves.empty())
    {
        std::cerr << "[RandomEngine] No legal moves available." << std::endl;
        return 0;
    }

    int index = std::rand() % moves.size();
    return moves[index];
}
