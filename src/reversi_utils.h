// reversi_utils.h

#pragma once

#include <cstdint>
#include "Board.h"

class Board;

Board get_start_position();
void print_bb(uint64_t bb);
void print_board(const Board& board);
uint64_t get_legal_moves(const Board& board);
