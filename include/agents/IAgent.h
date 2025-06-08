// IAgent.h

#pragma once
#include "core/Board.h"
#include <cstdint>

class IAgent
{
  public:
    virtual uint64_t get_move(const Board &board) = 0;
    virtual ~IAgent() = default;
};
