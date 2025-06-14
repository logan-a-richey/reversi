// board.h

#pragma once

#include <cstdint>
#include <vector>

#include "move.h"
#include "player.h"

class Board {
  public:
    uint64_t p1_bb;
    uint64_t p2_bb;
    int turn;

    uint64_t legal_bb;
    bool is_skipped;
    bool is_game_over;

    std::vector<Move> legal_moves;

    Board(uint64_t _p1, uint64_t _p2, int _turn)
        : p1_bb(_p1), p2_bb(_p2), turn(_turn), legal_bb(0), is_skipped(false), is_game_over(false) {
    }
};
