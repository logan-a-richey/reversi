// Engine.hpp
// Interface for engines

#pragma once
#include <cstdint>

class Board;

class Engine
{
  public:
    virtual ~Engine() = default;
    virtual uint64_t get_move(const Board &board) = 0;
};
