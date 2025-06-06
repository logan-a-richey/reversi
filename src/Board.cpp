// board.cpp

#include "board.h"
#include "movegen.h" // <- This should declare get_legal(const Board&)

Board::Board(u64 _white, u64 _black, char _turn)
    : white(_white), black(_black), turn(_turn)
{
    legal = get_legal(*this);  // Pass by reference
}
