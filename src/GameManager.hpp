// GameManager.hpp

#pragma once

#include <cstdint>
#include <string>
#include <vector>

// forward declare
class Board;
class PieceCount;

class GameManager
{
  public:
    GameManager() = default;
    ~GameManager() = default;

    // Public Variables
    bool is_playing_game = false;
    char game_result = '?'; // 'x', 'o', 'd', '?'

    // Public Methods
    void play_terminal_version(int game_mode);

    Board get_starting_position();

    void print_board(const Board &board);

    uint64_t get_terminal_move(const Board &board);

    uint64_t get_legal(const Board &board);

    uint64_t get_flipped(const Board &board, uint64_t move);

    Board make_move(const Board &board, uint64_t move);

    // char get_winner(const Board& board);
    PieceCount get_piece_count(const Board &board);

  private:
    // Helper function for finding legal moves
    uint64_t shift(uint64_t b, int dir);

    // TODO
    // Contain game history (for planned undo/redo feature)
    // std::vector<Board> board_states;
    // int state_index;
};
