// agent_bot_random.h

#pragma once

#include "agent_interface.h"
class Board;
class Move;

class AgentBotRandom : public AgentInterface {
  public:
    Move get_move(const Board &board) override;
    AgentBotRandom();
};
