// reversi_utils.h

#pragma once

#include <cstdint>
#include <vector>
#include <string>

#include "Board.h"

class Board;

//namespace Reversi 
//{
Board get_start_position();

void print_bb(uint64_t bb);

void print_board(const Board& board);

std::string get_str_move(uint64_t move);

uint64_t get_legal_moves(const Board& board);

uint64_t get_flipped(const Board& board, int64_t move);

Board make_move(const Board& board, uint64_t move);

std::vector<int> get_piece_count(const Board& board);

