// RandomEngine.hpp

#pragma once

#include "Engine.hpp"
#include <cstdint>

class Board;

class RandomEngine : public Engine
{
  public:
    RandomEngine();
    ~RandomEngine() override = default;
    uint64_t get_move(const Board &board) override;
};
