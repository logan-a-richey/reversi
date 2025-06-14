// reversi_utils.h

#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include "board.h"
#include "move.h"

/******************************************************************************/
// declarations:
void print_board(const Board &board);

void print_bb(uint64_t bb);

// conversion functions
uint64_t str_to_bb(const std::string &x);

std::string bb_to_str(uint64_t x);

int popcount64(uint64_t x);

// position setup
Board get_start_position();

void init_board_state(Board &board);

// legal moves
std::vector<Move> generate_legal_moves(const Board &board);

std::optional<Move> find_move(const Board &board, const std::string &symbol);

Board make_move(const Board &board, const Move &move);
