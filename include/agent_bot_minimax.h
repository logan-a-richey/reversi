// agent_bot_minimax.h

#pragma once

#include "agent_interface.h"
class Board;
class Move;

class AgentBotMinimax : public AgentInterface {
  public:
     Move get_move(const Board &board) override;
     AgentBotMinimax();
};
