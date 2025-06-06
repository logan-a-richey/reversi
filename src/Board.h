// board.h

#pragma once
#include <cstdint>

using u64 = uint64_t;

class Board {
public:
    u64 white;
    u64 black;
    char turn;     // 'B' or 'W'
    u64 legal;     // bitboard of legal moves

    Board(u64 _white, u64 _black, char _turn);
};
