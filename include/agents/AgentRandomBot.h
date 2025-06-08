// AgentRandomBot.h

#pragma once

#include "IAgent.h"
#include <cstdint>

class Board;

class AgentRandomBot : public IAgent
{
  public:
    AgentRandomBot();
    uint64_t get_move(const Board &board) override;
};
