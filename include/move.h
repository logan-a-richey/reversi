// move.h

#pragma once

#include <cstdint>
#include <string>

class Move {
public:
  uint64_t move_bb;
  uint64_t flipped_bb;
  std::string symbol;

  Move(uint64_t _move_bb, uint64_t _flipped_bb, std::string _symbol)
      : move_bb(_move_bb), flipped_bb(_flipped_bb), symbol(_symbol) {}
};
