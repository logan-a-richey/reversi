// board.cpp

#include "board.h"

#include <cstdint>

Board::Board(uint64_t _p1, uint64_t _p2, int _turn)
    : p1_bb(_p1), p2_bb(_p2), turn(_turn), legal_bb(0), is_skipped(false), is_game_over(false)
{
}
