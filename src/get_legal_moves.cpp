// move_gen.cpp

#include <cstdint>

#include "Board.h"

constexpr uint64_t FULL_BOARD     = 0xffffffffffffffff;
constexpr uint64_t NOT_LEFT_EDGE  = 0xfefefefefefefefe;
constexpr uint64_t NOT_RIGHT_EDGE = 0x7f7f7f7f7f7f7f7f;

inline uint64_t shift(uint64_t b, int dir) {
    if (dir > 0) 
    {
        return b << dir;
    }
    else        
    {
        return b >> -dir;
    }
}

// Core scanning function (template for all directions)
uint64_t slide_direction(uint64_t player, uint64_t opponent, int dir, uint64_t mask) 
{
    uint64_t result = 0;
    uint64_t temp = shift(player, dir) & opponent;
    
    // max flips in one direction is 6
    for (int i = 0; i < 5; ++i) 
    { 
        temp = shift(temp, dir) & opponent;
    }

    temp = shift(temp, dir) & ~ (player | opponent); // empty square
    return temp;
}

uint64_t get_legal_moves(const Board& board)
{
    uint64_t legal = 0;
    
    uint64_t plr = 0;
    uint64_t opp = 0;
    if board.turn == 'W'
    {
        plr = board.white;
        opp = board.black;
    }
    else
    {
        plr = board.black;
        opp = board.white;
    }


    legal |= slide_direction(plr, opp,  8, FULL_BOARD);         // north
    legal |= slide_direction(plr, opp, -8, FULL_BOARD);         // south
    legal |= slide_direction(plr, opp,  1, NOT_LEFT_EDGE);      // east
    legal |= slide_direction(plr, opp, -1, NOT_RIGHT_EDGE);     // west
    legal |= slide_direction(plr, opp,  9, NOT_LEFT_EDGE);      // northeast
    legal |= slide_direction(plr, opp,  7, NOT_RIGHT_EDGE);     // northwest
    legal |= slide_direction(plr, opp, -7, NOT_LEFT_EDGE);      // southeast
    legal |= slide_direction(plr, opp, -9, NOT_RIGHT_EDGE);     // southwest

    return legal;
}

