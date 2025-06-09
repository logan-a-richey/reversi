// reversi_utils.cpp

#include "reversi_utils.h"

#include <iostream>
#include "board.h"

void print_board(const Board& board)
{
  uint64_t mask; 

  std::cout << "  a b c d e f g h";
  for (int i=0; i<64; ++i)
  {
    if (i%8 == 0) {
      std::cout << std::endl;
      std::cout << i / 8 + 1 << " ";
    }
    mask = 1ULL << i;
    if (mask & board.p1_bb) std::cout << "1 ";
    else if (mask & board.p2_bb) std::cout << "2 ";
    else if (mask & board.legal_bb) std::cout << "X ";
    else std::cout << ". ";
  }

}


