// AgentMinimax.h

#pragma once

#include <cstdint>
#include "IAgent.h"

class Board;

class AgentMinimax : public IAgent
{
public:
    uint64_t get_move(const Board& board) override;

private:
    int evaluate(const Board& board);
    int minimax(const Board& board, int depth, int alpha, int beta);
};

