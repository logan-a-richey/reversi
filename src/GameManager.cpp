// GameManager.cpp

#include <cctype>  // for std::tolower()
#include <cstdint> // for uint64_t
#include <iomanip>
#include <iostream>
#include <limits>
#include <regex>
#include <string>

#include "Board.hpp"
#include "GameManager.hpp"
#include "GameMode.hpp"
#include "PieceCount.hpp"

constexpr uint64_t FILE_A = 0x0101010101010101ULL;
constexpr uint64_t FILE_H = 0x8080808080808080ULL;

/*****************************************************************************/
// Public:

// TODO
uint64_t GameManager::get_terminal_move(const Board &board) {
    static std::regex pattern("^[a-h][1-8]$");

    // std::cout << "[INFO] In get_terminal_move" << std::endl;

    while (true) {
        std::string str_move;

        if (board.turn == 'b')
            std::cout << "Player X to move: ";
        else
            std::cout << "Player O to move: ";

        std::cin >> str_move;

        if (std::regex_match(str_move, pattern)) {
            char file = str_move[0];
            char rank = str_move[1];

            int col = file - 'a';
            int row = rank - '1';

            int bit_index = row * 8 + col;

            uint64_t int_move = 1ULL << bit_index;
            if (int_move & board.legal) {
                return int_move;
            } else {
                std::cout << "That is not a legal move. Try again." << std::endl;
            }
        } else {
            std::cout << "Invalid input. Expected format like 'a1' or 'h8'." << std::endl;
            continue;
        }
    }
}

void GameManager::play_terminal_version([[maybe_unused]] int mode = HUMAN_HUMAN) {
    std::cout << "Playing game." << std::endl;

    // TODO
    // Engine engine;

    Board board = get_starting_position();

    print_board(board);

    is_playing_game = true;

    bool b_is_human = true;
    bool w_is_human = true;

    // Set Mode
    switch (mode) {
        case HUMAN_BOT:
            w_is_human = false;
            break;
        case BOT_HUMAN:
            b_is_human = false;
            break;
        case BOT_BOT:
            b_is_human = false;
            w_is_human = false;
            break;
        default:
            break;
    }

    // Game Loop:
    while (is_playing_game) {
        // Move Input:
        std::string str_move = "";
        uint64_t int_move = 0;

        // White Engine
        if ((board.turn == 'w') && !w_is_human) {
            std::cout << "[INFO] COMPUTER WHITE: " << std::endl;
        } else if ((board.turn == 'b') && !b_is_human) {
            std::cout << "[INFO] COMPUTER BLACK: " << std::endl;
        } else {
            std::cout << "[INFO] In human move" << std::endl;
        }

        int_move = get_terminal_move(board); // WAIT FOR USER INPUT

        // Make the move:
        board = make_move(board, int_move);

        // Handle turn skipping
        if (board.legal == 0) {
            std::cout << "No legal moves for player " << board.turn << ". Skipping turn."
                      << std::endl;

            board.turn = (board.turn == 'b') ? 'w' : 'b';
            board.legal = get_legal(board);

            // If both players have no moves, end the game
            if (board.legal == 0) {
                is_playing_game = false;
                break;
            }
        }

        print_board(board);
    }

    // Exit message
    PieceCount count = get_piece_count(board);
    if (count.white > count.black) {
        std::cout << "Player White won the game. Score: " << count.white << " : " << count.black
                  << std::endl;
    } else if (count.black > count.white) {
        std::cout << "Player Black won the game. Score: " << count.white << " : " << count.black
                  << std::endl;
    } else {
        std::cout << "Game drawn. Score: " << count.white << " : " << count.black << std::endl;
    }

    std::cout << "Bye!" << std::endl;
}

PieceCount GameManager::get_piece_count(const Board &board) {
    int black_count = 0;
    int white_count = 0;

    uint64_t compare = 1ULL << 63;
    while (compare) {
        if (compare & board.black) black_count += 1;
        if (compare & board.white) white_count += 1;
        compare >>= 1;
    }

    return PieceCount(black_count, white_count);
}

Board GameManager::get_starting_position() {
    uint64_t white = 0x0000001008000000;
    uint64_t black = 0x0000000810000000;
    int turn = 'b';

    Board board(white, black, turn);
    board.legal = get_legal(board);

    return board;
}

void GameManager::print_board(const Board &board) {
    /*
     * a1 b1 c1 .. h1
     * a2 b2 c2 .. h2
     * a3 b3 c3 .. h3
     * .. .. .. .. ..
     * a8 b8 c8 .. h8
     **/

    uint64_t compare = 1;

    std::cout << "  a b c d e f g h";
    for (int i = 0; i < 8; ++i) {
        std::cout << "\n" << i + 1 << " ";
        for (int j = 0; j < 8; ++j) {
            if (board.white & compare)
                std::cout << "o ";
            else if (board.black & compare)
                std::cout << "x ";
            else if (board.legal & compare)
                std::cout << "* ";
            else
                std::cout << ". ";
            compare <<= 1;
        }
    }
    std::cout << std::endl;
}

uint64_t GameManager::get_legal(const Board &board) {
    uint64_t player = (board.turn == 'b') ? board.black : board.white;
    uint64_t opponent = (board.turn == 'b') ? board.white : board.black;
    uint64_t empty = ~(player | opponent);

    uint64_t legal_moves = 0;

    // Direction masks
    const int directions[8] = {1, -1, 8, -8, 9, -9, 7, -7};

    for (int d = 0; d < 8; ++d) {
        int dir = directions[d];
        uint64_t mask = opponent;
        uint64_t edge_mask = ~0ULL;

        // Prevent wrapping at edges
        if (dir == 1 || dir == -7 || dir == 9) edge_mask &= ~FILE_H;
        if (dir == -1 || dir == -9 || dir == 7) edge_mask &= ~FILE_A;
        if (dir == -9 || dir == 7) edge_mask &= ~FILE_A; // SW/NW
        if (dir == 9 || dir == -7) edge_mask &= ~FILE_H; // NE/SE

        uint64_t potential = shift(player, dir) & mask & edge_mask;

        while (potential) {
            uint64_t next = shift(potential, dir) & edge_mask;

            // Squares that are empty and follow a chain of opponent pieces
            legal_moves |= next & empty;

            // Continue if the next in line is also an opponent
            potential = next & opponent;
        }
    }

    return legal_moves;
}

uint64_t GameManager::get_flipped(const Board &board, uint64_t move) {
    uint64_t player = (board.turn == 'b') ? board.black : board.white;
    uint64_t opponent = (board.turn == 'b') ? board.white : board.black;

    uint64_t flipped = 0;

    const int directions[8] = {1, -1, 8, -8, 9, -9, 7, -7};

    for (int d = 0; d < 8; ++d) {
        int dir = directions[d];
        uint64_t edge_mask = ~0ULL;

        if (dir == 1 || dir == -7 || dir == 9) edge_mask &= ~FILE_H;
        if (dir == -1 || dir == -9 || dir == 7) edge_mask &= ~FILE_A;
        if (dir == -9 || dir == 7) edge_mask &= ~FILE_A;
        if (dir == 9 || dir == -7) edge_mask &= ~FILE_H;

        uint64_t captured = 0;
        uint64_t current = shift(move, dir) & edge_mask;

        while (current && (current & opponent)) {
            captured |= current;
            current = shift(current, dir) & edge_mask;
        }

        if (current & player) {
            flipped |= captured;
        }
    }

    return flipped;
}

Board GameManager::make_move(const Board &board, uint64_t move) {
    uint64_t flipped = get_flipped(board, move);

    uint64_t new_white = board.white;
    uint64_t new_black = board.black;

    if (board.turn == 'b') {
        new_black |= move;
        new_black |= flipped;
        new_white &= ~flipped;
    } else {
        new_white |= move;
        new_white |= flipped;
        new_black &= ~flipped;
    }

    char new_turn = (board.turn == 'b') ? 'w' : 'b';
    Board new_board(new_white, new_black, new_turn);
    new_board.legal = get_legal(new_board);
    return new_board;
}

/*****************************************************************************/
// Private:

uint64_t GameManager::shift(uint64_t b, int dir) {
    switch (dir) {
        case 1:
            return (b << 1) & ~FILE_H; // East
        case -1:
            return (b >> 1) & ~FILE_A; // West
        case 8:
            return (b << 8); // North
        case -8:
            return (b >> 8); // South
        case 9:
            return (b << 9) & ~FILE_H; // NE
        case -9:
            return (b >> 9) & ~FILE_A; // SW
        case 7:
            return (b << 7) & ~FILE_A; // NW
        case -7:
            return (b >> 7) & ~FILE_H; // SE
        default:
            return 0;
    }
}
