// reversi_utils.cpp

#include <iostream>
#include <cstdint>
#include <vector>

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

// Border masks
constexpr uint64_t BORDER_N = 0x00000000000000FFULL;
constexpr uint64_t BORDER_S = 0xFF00000000000000ULL;
constexpr uint64_t BORDER_E = 0x8080808080808080ULL;
constexpr uint64_t BORDER_W = 0x0101010101010101ULL;

using DirectionScanner = bool(*)(uint64_t, uint64_t, uint64_t);

// NORTH
static bool search_n(uint64_t plr, uint64_t opp, uint64_t sq) {
    uint64_t mask = sq;
    bool seen_opp = false;
    while (!(mask & BORDER_N)) {
        mask <<= 8;
        if ((mask & ~(plr | opp)) != 0) return false;
        if (mask & opp) seen_opp = true;
        else if (mask & plr) return seen_opp;
        else return false;
    }
    return false;
}

// SOUTH
static bool search_s(uint64_t plr, uint64_t opp, uint64_t sq) {
    uint64_t mask = sq;
    bool seen_opp = false;
    while (!(mask & BORDER_S)) {
        mask >>= 8;
        if ((mask & ~(plr | opp)) != 0) return false;
        if (mask & opp) seen_opp = true;
        else if (mask & plr) return seen_opp;
        else return false;
    }
    return false;
}

// EAST
static bool search_e(uint64_t plr, uint64_t opp, uint64_t sq) {
    uint64_t mask = sq;
    bool seen_opp = false;
    while (!(mask & BORDER_E)) {
        mask <<= 1;
        if ((mask & ~(plr | opp)) != 0) return false;
        if (mask & opp) seen_opp = true;
        else if (mask & plr) return seen_opp;
        else return false;
    }
    return false;
}

// WEST
static bool search_w(uint64_t plr, uint64_t opp, uint64_t sq) {
    uint64_t mask = sq;
    bool seen_opp = false;
    while (!(mask & BORDER_W)) {
        mask >>= 1;
        if ((mask & ~(plr | opp)) != 0) return false;
        if (mask & opp) seen_opp = true;
        else if (mask & plr) return seen_opp;
        else return false;
    }
    return false;
}

// NORTHEAST
static bool search_ne(uint64_t plr, uint64_t opp, uint64_t sq) {
    uint64_t mask = sq;
    bool seen_opp = false;
    while (!(mask & BORDER_N) && !(mask & BORDER_E)) {
        mask <<= 9;
        if ((mask & ~(plr | opp)) != 0) return false;
        if (mask & opp) seen_opp = true;
        else if (mask & plr) return seen_opp;
        else return false;
    }
    return false;
}

// NORTHWEST
static bool search_nw(uint64_t plr, uint64_t opp, uint64_t sq) {
    uint64_t mask = sq;
    bool seen_opp = false;
    while (!(mask & BORDER_N) && !(mask & BORDER_W)) {
        mask <<= 7;
        if ((mask & ~(plr | opp)) != 0) return false;
        if (mask & opp) seen_opp = true;
        else if (mask & plr) return seen_opp;
        else return false;
    }
    return false;
}

// SOUTHEAST
static bool search_se(uint64_t plr, uint64_t opp, uint64_t sq) {
    uint64_t mask = sq;
    bool seen_opp = false;
    while (!(mask & BORDER_S) && !(mask & BORDER_E)) {
        mask >>= 7;
        if ((mask & ~(plr | opp)) != 0) return false;
        if (mask & opp) seen_opp = true;
        else if (mask & plr) return seen_opp;
        else return false;
    }
    return false;
}

// SOUTHWEST
static bool search_sw(uint64_t plr, uint64_t opp, uint64_t sq) {
    uint64_t mask = sq;
    bool seen_opp = false;
    while (!(mask & BORDER_S) && !(mask & BORDER_W)) {
        mask >>= 9;
        if ((mask & ~(plr | opp)) != 0) return false;
        if (mask & opp) seen_opp = true;
        else if (mask & plr) return seen_opp;
        else return false;
    }
    return false;
}

uint64_t get_legal_moves(const Board& board)
{
    static const std::vector<DirectionScanner> direction_scanners = {
        &search_n, &search_s, &search_e, &search_w,
        &search_ne, &search_nw, &search_se, &search_sw
    };

    uint64_t legal_moves = 0;
    uint64_t plr = 0;
    uint64_t opp = 0;

    if (board.turn == 'B') {
        plr = board.black;
        opp = board.white;
    } else if (board.turn == 'W') {
        plr = board.white;
        opp = board.black;
    } else {
        std::cerr << "[E: get_legal_moves] Invalid turn: " << board.turn << std::endl;
        return 0;
    }

    uint64_t occ = board.white | board.black;
    for (int i = 0; i < 64; ++i)
    {
        uint64_t sq = 1ULL << i;
        if (sq & occ) continue;

        for (auto d : direction_scanners) {
            if (d(plr, opp, sq)) {
                legal_moves |= sq;
                break; // One valid direction is enough
            }
        }
    }

    return legal_moves;
}
