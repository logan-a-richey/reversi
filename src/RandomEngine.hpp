// RandomEngine.hpp

#pragma once

#include <cstdint>
#include "Engine.hpp"

class Board;

class RandomEngine : public Engine
{
  public:
    RandomEngine();
    ~RandomEngine() override = default;
    uint64_t get_move(const Board &board) override;
};
