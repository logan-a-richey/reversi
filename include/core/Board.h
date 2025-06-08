// Board.h

#pragma once

#include <cstdint>

class Board
{
  public:
    Board(uint64_t b, uint64_t w, char t);
    
    uint64_t black; // bitboard of all black piece
    uint64_t white; // bitboard of all white pieces
    char turn;      // turn: can be 'B' or 'W'
    uint64_t legal; // bitboard of legal moves
    bool is_skipped;
    bool is_game_over;
};
