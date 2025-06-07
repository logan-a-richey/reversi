// AgentHumanTerminal.h

#pragma once

#include <cstdint>
#include "IAgent.h"

class Board;

class AgentHumanTerminal : public IAgent 
{
public:
    uint64_t get_move(const Board& board) override;
};


