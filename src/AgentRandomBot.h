// AgentRandomBot.h

#pragma once

#include <cstdint>
#include "IAgent.h"

class Board;

class AgentRandomBot : public IAgent 
{
public:
    AgentRandomBot();
    uint64_t get_move(const Board& board) override;
};
