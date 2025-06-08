// Board.cpp

#include <cstdint>
#include <iostream>

#include "core/Board.h"
#include "core/reversi_utils.h"

Board::Board(uint64_t b, uint64_t w, char t)
    : black(b), white(w), turn(t), legal(0), is_skipped(false), is_game_over(false)
{
    is_game_over = false;
    legal = Reversi::get_legal_moves(*this);

    // skip 1
    if (legal != 0)
        return;

    is_skipped = true;
    turn = (turn == 'B') ? 'W' : 'B';
    legal = Reversi::get_legal_moves(*this);

    // skip 2
    if (legal != 0)
        return;
    
    is_game_over = true;
}
