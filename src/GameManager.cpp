// GameManager.cpp

#include <iostream>
#include <iomanip>
#include <cstdint>

#include "GameManager.hpp"
#include "Board.hpp"

constexpr uint64_t FILE_A = 0x0101010101010101ULL;
constexpr uint64_t FILE_H = 0x8080808080808080ULL;

/*****************************************************************************/
// Public:

void GameManager::play_terminal_version(){
    std::cout << "Playing game.\n";

    Board board = get_starting_position();
    print_board(board);
    std::cout << "legal moves. dec: " << board.legal 
        << " hex: 0x" << std::hex << std::setw(16) << std::setfill('0') << board.legal << "\n";
}

Board GameManager::get_starting_position(){
    // We could represent this in hex, but I prefer binary so we can see the position easier
    uint64_t white = 0x0000001008000000;
    uint64_t black = 0x0000000810000000;
    int turn = 'b';
    Board board(white, black, turn);
    board.legal = get_legal(board);
    return board;
}

void GameManager::print_board(const Board& board)
{
    /*
     * a1 b1 c1 .. h1
     * a2 b2 c2 .. h2
     * a3 b3 c3 .. h3
     * .. .. .. .. ..
     * a8 b8 c8 .. h8
    **/
    
    uint64_t compare = 1;

    std::cout << "  a b c d e f g h";
    for (int i = 0; i < 8; ++i)
    {
        std::cout << "\n" << i + 1 << " ";
        for (int j = 0; j < 8; ++j)
        {
            if (board.white & compare) std::cout << "o ";
            else if (board.black & compare) std::cout << "x ";
            else if (board.legal & compare) std::cout << "* ";
            else std::cout << ". ";
            compare <<= 1;
        }
    }
    std::cout << "\n";
}

uint64_t GameManager::get_legal(const Board& board)
{
    uint64_t player = (board.turn == 'b') ? board.black : board.white;
    uint64_t opponent = (board.turn == 'b') ? board.white : board.black;
    uint64_t empty = ~(player | opponent);

    uint64_t legal_moves = 0;

    // Direction masks
    const int directions[8] = { 1, -1, 8, -8, 9, -9, 7, -7 };

    for (int d = 0; d < 8; ++d)
    {
        int dir = directions[d];
        uint64_t mask = opponent;
        uint64_t edge_mask = ~0ULL;

        // Prevent wrapping at edges
        if (dir == 1 || dir == -7 || dir == 9) edge_mask &= ~FILE_H;
        if (dir == -1 || dir == -9 || dir == 7) edge_mask &= ~FILE_A;
        if (dir == -9 || dir == 7) edge_mask &= ~FILE_A; // SW/NW
        if (dir == 9 || dir == -7) edge_mask &= ~FILE_H; // NE/SE

        uint64_t potential = shift(player, dir) & mask & edge_mask;

        while (potential)
        {
            uint64_t next = shift(potential, dir) & edge_mask;

            // Squares that are empty and follow a chain of opponent pieces
            legal_moves |= next & empty;

            // Continue if the next in line is also an opponent
            potential = next & opponent;
        }
    }

    return legal_moves;
}


/*****************************************************************************/
// Private:

uint64_t GameManager::shift(uint64_t b, int dir) {
    switch (dir) {
        case 1: return (b << 1) & ~FILE_H;             // East
        case -1: return (b >> 1) & ~FILE_A;            // West
        case 8: return (b << 8);                       // North
        case -8: return (b >> 8);                      // South
        case 9: return (b << 9) & ~FILE_H;             // NE
        case -9: return (b >> 9) & ~FILE_A;            // SW
        case 7: return (b << 7) & ~FILE_A;             // NW
        case -7: return (b >> 7) & ~FILE_H;            // SE
        default: return 0;
    }
}
