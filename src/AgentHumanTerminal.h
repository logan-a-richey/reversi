// AgentHumanTerminal.h

#pragma once

#include "IAgent.h"
#include <cstdint>

class Board;

class AgentHumanTerminal : public IAgent
{
  public:
    uint64_t get_move(const Board &board) override;
};
