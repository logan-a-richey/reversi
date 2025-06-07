// IAgent.h

#pragma once
#include "Board.h"
#include <cstdint>

class IAgent 
{
public:
    virtual uint64_t get_move(const Board& board) = 0;
    virtual ~Agent() = default;
};

