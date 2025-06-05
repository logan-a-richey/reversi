// GameManager.hpp

#pragma once
#include <cstdint>
#include <vector>

// forward declare
class Board;

class GameManager{
public:
    int game_mode;
    
    // Constructor
    GameManager(int mode) : game_mode(mode) {}

    void play_terminal_version();
    
    Board get_starting_position();
    
    void print_board(const Board& board);

private:
    // Helper function for finding legal moves
    uint64_t shift(uint64_t b, int dir);

public:
    // a legal move consists of a sandwich of pieces in any of the cardinal directions
    // if current player does not have any legal moves, skip their turn
    // if both players do not have any legal moves, end the game, check winner
    uint64_t get_legal(const Board& board);
    
    // returns a list of flipped squares
    uint64_t get_flipped(const Board& board);

    // simulates a move
    Board make_move(const Board& board, uint64_t move);
    // simulate the move here with the correct piece flips
    // return the board back using automatic move semantics

    char get_winner(const Board& board); // return 'x', 'o', 'd'
    // if number of black tiles > white tiles, return 'x'
    // if number of white tiles > black tiles, return 'o'
    // else return 'd' for draw
private:
    std::vector<Board> board_states;
    int state_index;
};
