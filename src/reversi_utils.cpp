// reversi_utils.cpp

#include <iostream>
#include <cstdint>
#include <vector>
#include <functional>

#include "Board.h"
#include "reversi_utils.h"

/*****************************************************************************/
Board get_start_position(){
    uint64_t white = 0x0000001008000000ULL;
    uint64_t black = 0x0000000810000000ULL;
    char turn = 'B';
    
    Board start_position(black, white, turn);
    return start_position;
}

/*****************************************************************************/
void print_bb(uint64_t bb) {
    uint64_t bit = 1;
    int it = 0;
    for (int i = 0; i < 64; ++i) {
        if (i % 8 == 0 && i != 0) {
            std::cout << "\n";
        }
        
        if (bit << i & bb) {
            std::cout << "x ";
        } else {
            std::cout << ". ";
        }
        it++;
    }
    std::cout << std::endl;
}

void print_board(const Board& board) {
    std::cout << "  a b c d e f g h";
    uint64_t bit = 1;
    int it = 0;
    for (int i = 0; i < 64; ++i) {
        if (i % 8 == 0) {
            std::cout << "\n" << i / 8 + 1 << " ";
        }

        if (bit << i & board.black){
            std::cout << "x ";
        } else if (bit << i & board.white) {
            std::cout << "o ";
        } else if (bit << i & board.legal) {
            std::cout << "* ";
        } else {
            std::cout << ". ";
        }
    }
    std::cout << std::endl;
}

/*****************************************************************************/
// Get Legal:
// Border masks
constexpr uint64_t RANK_1 = 0x00000000000000FFULL;
constexpr uint64_t RANK_8 = 0xFF00000000000000ULL;

constexpr uint64_t FILE_A = 0x0101010101010101ULL;
constexpr uint64_t FILE_H = 0x8080808080808080ULL;

using DirectionScanner = bool(*)(uint64_t, uint64_t, uint64_t);

using ShiftFunc = std::function<uint64_t(uint64_t)>;

struct Direction
{
    ShiftFunc shift;
    uint64_t border_mask;
};

// TODO - check this 
static const std::vector<Direction> DIRECTIONS = {
    { [](uint64_t x){ return x << 8; }, RANK_8 }, // N
    { [](uint64_t x){ return x >> 8; }, RANK_1 }, // S
    { [](uint64_t x){ return x << 1; }, FILE_H }, // E
    { [](uint64_t x){ return x >> 1; }, FILE_A }, // W
    { [](uint64_t x){ return x << 9; }, RANK_8 | FILE_H }, // NE
    { [](uint64_t x){ return x << 7; }, RANK_8 | FILE_A }, // NW
    { [](uint64_t x){ return x >> 7; }, RANK_1 | FILE_H }, // SE
    { [](uint64_t x){ return x >> 9; }, RANK_1 | FILE_A }  // SW
};

static bool generic_search(uint64_t plr, uint64_t opp, uint64_t sq, const Direction& dir)
{
    // already at edge
    if (sq & dir.border_mask) 
    {
        return false; 
    }

    // compare bits
    uint64_t mask = sq;
    bool seen_opp = false;

    while (true)
    {
        mask = dir.shift(mask);
        if (mask == 0 || (mask & dir.border_mask)) {
            return false;
        }

        if (mask & opp) {
            seen_opp = true;
        } else if (mask & plr) {
            return seen_opp;
        } else {
            // empty square
            return false;
        }
    }
    return false;
}

uint64_t get_legal_moves(const Board& board)
{
    uint64_t legal_moves = 0;
    
    uint64_t plr = (board.turn == 'B') ? board.black : board.white;
    uint64_t opp = (board.turn == 'B') ? board.white : board.black;
    
    uint64_t occ = plr | opp;

    for (int i = 0; i < 64; ++i)
    {
        uint64_t sq = 1ULL << i;
        if (sq & occ) continue;

        for (const auto& dir : DIRECTIONS) 
        {
            if (generic_search(plr, opp, sq, dir))
            {
                legal_moves |= sq;
                // only break inside of this nested loop. 
                // will continue for all 64 squares.
                break;             
            }
        }
    }
    return legal_moves;
}

/*****************************************************************************/
// Flip tiles

// TODO
static uint64_t generic_flip(uint64_t plr, uint64_t opp, uint64_t sq, const Direction& dir)
{
    if (sq & dir.border_mask)
        return 0ULL;

    uint64_t flipped = 0;
    uint64_t mask = sq;

    while (true)
    {
        mask = dir.shift(mask);
        if (mask == 0 || (mask & dir.border_mask))
            return 0ULL;

        if (mask & opp)
            flipped |= mask;    
        else if (mask & plr)
            return flipped;
        else
            return 0ULL; // empty square
    }
    return 0ULL;
}

uint64_t get_flipped(const Board& board, uint64_t move)
{
    uint64_t flipped = 0ULL;

    uint64_t plr = (board.turn == 'B') ? board.black : board.white;
    uint64_t opp = (board.turn == 'B') ? board.white : board.black;

    for (const auto& dir : DIRECTIONS)
    {
        flipped |= generic_flip(plr, opp, move, dir);
    }

    return flipped;
}

/*****************************************************************************/
// Make move

Board make_move(const Board& board, uint64_t move)
{
    uint64_t flipped = get_flipped(board, move);
    uint64_t white = board.white ^ flipped;
    uint64_t black = board.black ^ flipped;
    
    if (board.turn == 'B') {
        black |= move;
    } else if (board.turn == 'W') {
        white |= move;
    }
    
    char turn = (board.turn == 'B') ? 'W' : 'B';
    
    Board new_board(black, white, turn);
    
    // if no moves, toggle turn back to current player
    if (new_board.legal == 0) {
        new_board.turn = board.turn;
    }
    
    // TODO
    // check for no legal moves in the game loop. 
    // if there are no legal moves, call game_over
    return new_board;
}

