/******************************************************************************/
// reversi_utils.cpp

#include "reversi_utils.h"

#include <cstdint>
#include <iostream>
#include <vector>

#include "player.h"
#include "board.h"
#include "move.h"

/******************************************************************************/
void print_board(const Board& board)
{
  uint64_t mask; 
  std::cout << "  a b c d e f g h";
  for (int i=0; i<64; ++i)
  {
    if (i%8 == 0) 
    {
      std::cout << std::endl;
      std::cout << i / 8 + 1 << " ";
    }
    mask = 1ULL << i;
    if (mask & board.p1_bb) std::cout << "1 ";
    else if (mask & board.p2_bb) std::cout << "2 ";
    else if (mask & board.legal_bb) std::cout << "X ";
    else std::cout << ". ";
  }
  std::cout << std::endl;
}

void print_bb(uint64_t bb)
{
  uint64_t mask; 
  std::cout << "  a b c d e f g h";
  for (int i=0; i<64; ++i)
  {
    if (i%8 == 0) 
    {
      std::cout << std::endl;
      std::cout << i / 8 + 1 << " ";
    }
    mask = 1ULL << i;
    if (mask & bb) std::cout << "X ";
    else std::cout << ". ";
  }
  std::cout << std::endl;
}

/******************************************************************************/
// convertion functions
uint64_t str_to_bb(const std::string& x)
{
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
  if (file_index < 0 || file_index > 7 || rank_index < 0 || rank_index > 7) 
  {
    return 0ULL; // invalid input
  }

  int square_index = rank_index * 8 + file_index;
  return 1ULL << square_index;
}

std::string bb_to_str(uint64_t x)
{
  if (x == 0) 
  {
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
int popcount64(uint64_t x)
{
  static constexpr uint64_t m1  = 0x5555555555555555ULL; // 0101...
  static constexpr uint64_t m2  = 0x3333333333333333ULL; // 0011...
  static constexpr uint64_t m4  = 0x0F0F0F0F0F0F0F0FULL; // 00001111...

  x -= (x >> 1) & m1;             // count of each 2 bits
  x = (x & m2) + ((x >> 2) & m2); // count of each 4 bits
  x = (x + (x >> 4)) & m4;        // count of each 8 bits
  x += x >> 8;
  x += x >> 16;
  x += x >> 32;
  return static_cast<int>(x & 0x7F);
}

/******************************************************************************/
Board get_start_position()
{
  uint64_t p1bb = 0;
  uint64_t p2bb = 0;

  p2bb |= str_to_bb("d4");
  p1bb |= str_to_bb("e4");
  p1bb |= str_to_bb("d5");
  p2bb |= str_to_bb("e5");

  Board start_position(p1bb, p2bb, PLAYER1); 
  return start_position; 
}

/******************************************************************************/
// legal move generation

std::vector<Move> generate_legal_moves(const Board& baord)
{
  // TODO
  return {};
}

