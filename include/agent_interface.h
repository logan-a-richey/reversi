// agent_interface.h

#pragma once

class Board;
class Move;

class AgentInterface {
  public:
    virtual ~AgentInterface() = default;
    virtual Move get_move(const Board &board) = 0;
};
