// agent_human_terminal.h

#pragma once

#include "agent_interface.h"
class Board;
class Move;

class AgentHumanTerminal : public AgentInterface
{
  public:
    Move get_move(const Board &board) override;
};
