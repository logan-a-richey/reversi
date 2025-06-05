// Board.hpp

#pragma once

#include <cstdint>

class Board {
public:
    uint64_t white; // represent squares of white pieces
    uint64_t black; // represent squares of black pieces
    char turn;
    uint64_t legal; // represent squares of legal moves
    
    // Constructor
    Board(uint64_t _white, uint64_t _black, char _turn) : 
        white(_white), black(_black), turn(_turn), legal(0) {}
};

