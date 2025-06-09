// move.h

#pragma once

#include <cstdint>
#include <string>

class Move {
public:
  uint64_t move;
  uint64_t flipped;
  std::string symbol;

  Move(uint64_t move, uint64_t flipped, std::string symbol) :
     move(_move),  flipped(_flipped),  symbol(_symbol) {}
};


