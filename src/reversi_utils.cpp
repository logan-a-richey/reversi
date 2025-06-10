/******************************************************************************/
// reversi_utils.cpp

#include "reversi_utils.h"

#include <cstdint>
#include <functional>
#include <iostream>
#include <optional>
#include <vector>

#include "board.h"
#include "move.h"
#include "player.h"

/******************************************************************************/
void print_board(const Board &board) {
  uint64_t mask;
  std::cout << "  a b c d e f g h";
  for (int i = 0; i < 64; ++i) {
    if (i % 8 == 0) {
      std::cout << std::endl;
      std::cout << i / 8 + 1 << " ";
    }
    mask = 1ULL << i;
    if (mask & board.p1_bb)
      std::cout << "1 ";
    else if (mask & board.p2_bb)
      std::cout << "2 ";
    else if (mask & board.legal_bb)
      std::cout << "* ";
    else
      std::cout << "_ ";
  }
  std::cout << std::endl;
}

void print_bb(uint64_t bb) {
  uint64_t mask;
  std::cout << "  a b c d e f g h";
  for (int i = 0; i < 64; ++i) {
    if (i % 8 == 0) {
      std::cout << std::endl;
      std::cout << i / 8 + 1 << " ";
    }
    mask = 1ULL << i;
    if (mask & bb)
      std::cout << "X ";
    else
      std::cout << ". ";
  }
  std::cout << std::endl;
}

/******************************************************************************/
// convertion functions
uint64_t str_to_bb(const std::string &x) {
  // bit 1 = h1 (lower right corner)
  // bit 64 = a8 (upper right corner)
  // input: <char file><char rank>
  // e.g.: a1
  // TODO

  if (x.size() != 2) {
    return 0ULL; // invalid input
  }

  char file = x[0];
  char rank = x[1];

  int file_index = file - 'a'; // "a" to "h" => 0 to 7
  int rank_index = rank - '1'; // "1" to "8" => 0 to 7

  // check bounds
  if (file_index < 0 || file_index > 7 || rank_index < 0 || rank_index > 7) {
    return 0ULL; // invalid input
  }

  int square_index = rank_index * 8 + file_index;
  return 1ULL << square_index;
}

std::string bb_to_str(uint64_t x) {
  if (x == 0) {
    return "";
  }

  int index = __builtin_ctzll(x); // count trailing zeros

  int file_index = index % 8;
  int rank_index = index / 8;

  char file = 'a' + file_index;
  char rank = '1' + rank_index;

  std::string output = "";
  output += file;
  output += rank;

  return output;
}

/******************************************************************************/
// counts number of bits in a bitboard using Hamming weight algorithm
int popcount64(uint64_t x) {
  static constexpr uint64_t m1 = 0x5555555555555555ULL; // 0101...
  static constexpr uint64_t m2 = 0x3333333333333333ULL; // 0011...
  static constexpr uint64_t m4 = 0x0F0F0F0F0F0F0F0FULL; // 00001111...

  x -= (x >> 1) & m1;             // count of each 2 bits
  x = (x & m2) + ((x >> 2) & m2); // count of each 4 bits
  x = (x + (x >> 4)) & m4;        // count of each 8 bits
  x += x >> 8;
  x += x >> 16;
  x += x >> 32;
  return static_cast<int>(x & 0x7F);
}

/******************************************************************************/
Board get_start_position() {
  uint64_t p1bb = 0;
  uint64_t p2bb = 0;

  p2bb |= str_to_bb("d4");
  p1bb |= str_to_bb("e4");
  p1bb |= str_to_bb("d5");
  p2bb |= str_to_bb("e5");

  Board start_position(p1bb, p2bb, PLAYER1);
  return start_position;
}

void init_board_state(Board &board) {
  auto moves = generate_legal_moves(board);

  if (!moves.empty()) {
    board.legal_moves = std::move(moves);
    board.legal_bb = 0;
    for (const auto &m : board.legal_moves) {
      board.legal_bb |= m.move_bb;
    }
    return;
  }

  // No moves? Skip turn
  board.is_skipped = true;
  board.turn = (board.turn == PLAYER1) ? PLAYER2 : PLAYER1;

  moves = generate_legal_moves(board);
  if (!moves.empty()) {
    board.legal_moves = std::move(moves);
    board.legal_bb = 0;
    for (const auto &m : board.legal_moves) {
      board.legal_bb |= m.move_bb;
    }
    return;
  }

  // No legal moves on second turn either
  board.is_game_over = true;
}

/******************************************************************************/
// legal move generation

// Border masks
constexpr uint64_t RANK_1 = 0x00000000000000FFULL;
constexpr uint64_t RANK_8 = 0xFF00000000000000ULL;
constexpr uint64_t FILE_A = 0x0101010101010101ULL;
constexpr uint64_t FILE_H = 0x8080808080808080ULL;

// Lambda shift
using ShiftFunc = std::function<uint64_t(uint64_t)>;

class Direction {
public:
  ShiftFunc shift;
  uint64_t border_mask;
};

static const std::vector<Direction> DIRECTIONS = {
    {[](uint64_t x) { return x << 8; }, RANK_8},          // N
    {[](uint64_t x) { return x >> 8; }, RANK_1},          // S
    {[](uint64_t x) { return x << 1; }, FILE_H},          // E
    {[](uint64_t x) { return x >> 1; }, FILE_A},          // W
    {[](uint64_t x) { return x << 9; }, RANK_8 | FILE_H}, // NE
    {[](uint64_t x) { return x << 7; }, RANK_8 | FILE_A}, // NW
    {[](uint64_t x) { return x >> 7; }, RANK_1 | FILE_H}, // SE
    {[](uint64_t x) { return x >> 9; }, RANK_1 | FILE_A}  // SW
};

static uint64_t generic_flip(uint64_t plr, uint64_t opp, uint64_t sq,
                             const Direction &dir) {
  uint64_t flipped = 0;
  uint64_t mask = sq;

  while (true) {
    if (mask & dir.border_mask) return 0ULL; // would cross the edge

    mask = dir.shift(mask);
    if (mask == 0) return 0ULL;

    if (mask & opp)
      flipped |= mask;
    else if (mask & plr)
      return flipped;
    else
      return 0ULL; // empty square
  }
  return 0ULL;
}

std::vector<Move> generate_legal_moves(const Board &board) {
  std::vector<Move> moves;

  uint64_t plr = (board.turn == PLAYER1) ? board.p1_bb : board.p2_bb;
  uint64_t opp = (board.turn == PLAYER1) ? board.p2_bb : board.p1_bb;
  uint64_t occ = plr | opp;

  for (int i = 0; i < 64; ++i) {
    uint64_t sq = 1ULL << i;

    if (sq & occ) continue;

    bool legal = false;
    uint64_t total_flipped = 0;

    for (const auto &dir : DIRECTIONS) {
      uint64_t flipped = generic_flip(plr, opp, sq, dir);
      if (flipped) {
        legal = true;
        total_flipped |= flipped;
      }
    }

    if (legal) {
      // convert 1ULL << i to something like "d3"
      std::string symbol = bb_to_str(sq);
      moves.emplace_back(sq, total_flipped, symbol);
    }
  }

  return moves;
}

std::optional<Move> find_move(const Board &board, const std::string &symbol) {
  for (auto m : board.legal_moves) {
    if (symbol == m.symbol) {
      return m;
    }
  }
  return std::nullopt;
}

Board make_move(const Board &board, const Move &move) {
  // Copy current state
  Board new_board(board.p1_bb, board.p2_bb, board.turn);

  // Player and opponent bitboards
  uint64_t &plr =
      (new_board.turn == PLAYER1) ? new_board.p1_bb : new_board.p2_bb;
  uint64_t &opp =
      (new_board.turn == PLAYER1) ? new_board.p2_bb : new_board.p1_bb;

  // Update player and opponent bitboards
  plr |= move.move_bb;
  plr |= move.flipped_bb;
  opp &= ~move.flipped_bb;

  // Flip turn
  new_board.turn = (new_board.turn == PLAYER1) ? PLAYER2 : PLAYER1;

  // Recalculate board state
  init_board_state(new_board);

  return new_board;
}
