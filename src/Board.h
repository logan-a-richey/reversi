// Board.h

#pragma once

#include <cstdint>

class Board
{
  public:
    // bitboard representing location of all black piece
    uint64_t black;

    // bitboard representing location of all white pieces
    uint64_t white;

    // turn: can be 'B' or 'W'
    char turn;

    // legal moves are loaded into the position upon construction
    // legal moves need to be recalculated if we mutate the turn variable
    uint64_t legal;

    bool is_skipped;
    bool is_game_over;

    // constructor
    Board(uint64_t b, uint64_t w, char t);
};
