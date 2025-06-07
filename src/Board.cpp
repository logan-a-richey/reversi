// Board.cpp

#include <cstdint>

#include "Board.h"
#include "reversi_utils.h"

Board::Board(uint64_t b, uint64_t w, char t) : black(b), white(w), turn(t) 
{
    legal = get_legal_moves(*this);
}
