// board.h

# pragma once

#include <cstdint>
#include <vector>

#include "player.h"
#include "move.h"

class Board {
public:
  uint64_t p1_bb;
  uint64_t p2_bb;
  uint64_t legal_bb;
  Player turn;

  std::vector<Move> legal_moves;
};

