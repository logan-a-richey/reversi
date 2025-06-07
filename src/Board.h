// Board.h

#pragma once

#include <cstdint>

class Board 
{
public:
    uint64_t white;
    uint64_t black;
    char turn; // 'W','B'
    uint64_t legal;

    Board(uint64_t b, uint64_t w, char t);
};

