// board.cpp

#include "player.h"
#include "board.h"
#include "reversi_utils.h"

Board::Board(uint64_t _p1, uint64_t _p2, int _turn) :
  p1_bb(_p1), p2_bb(_p2), legal_bb(_turn)
{
  std::vector<Move> moves;
  moves = generate_legal_moves(*this);

  // if there are legal moves, add it to the list, and update legal_bb
  if (legal_moves.size() != 0)
  {
    this->legal_moves = moves; // std::move ?

    for (auto m : moves)
    {
      legal_bb |= m.move_bb;
    }
    return;
  }
  
  // turn skip
  // swap sides
  this->is_skipped = true;
  turn = (turn == PLAYER1) ? PLAYER2 : PLAYER1;
  
  moves.clear();
  this->legal_bb = 0;
  moves = generate_legal_moves(*this);

  // if there are legal moves, add it to the list, and update legal_bb
  if (legal_moves.size() != 0)
  {
    this->legal_moves = moves; // std::move ?

    for (auto m : moves)
    {
      legal_bb |= m.move_bb;
    }
    return;
  }

  // second turn skip
  this->is_game_over = true;
  return;
}

