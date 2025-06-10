// game_manager.cpp

#include <iostream>
#include <optional>

#include "player.h"
#include "reversi_utils.h"
#include "game_manager.h"
#include "agent_factory.h"

// Debug
/*
void test_case()
{
  uint64_t white = str_to_bb("a1");
  uint64_t black = str_to_bb("a2");
  uint64_t move_bb = str_to_bb("a3");
  
  Board board(black, white, PLAYER2); // White to play
  init_board_state(board);
  
  std::optional<Move> move = find_move(board, "a3");
  if (!move)
  {
    std::cout << "No move found" << std::endl;
    return;
  }

  print_board(board);
  
  board = make_move(board, *move);
  init_board_state(board);
  
  print_board(board);
}
*/

void GameManager::run(int p1_t, int p2_t)
{
  std::cout << "Playing game." << std::endl;

  // Debug
  /*
  test_case();
  return;
  */

  Board board = get_start_position();
  init_board_state(board);
  
  std::unique_ptr<AgentInterface> p1a = create_agent(p1_t); 
  std::unique_ptr<AgentInterface> p2a = create_agent(p2_t);

  // --- Game Loop --- 
  while (!board.is_game_over)
  {
    // Terminal turn message:
    if (board.is_skipped) 
    {
      if (board.turn == 'B') 
      {
        std::cout << "White turn skipped. Black to play: " << std::endl;
      }
      else 
      {
        std::cout << "Black turn skipped. White to play: " << std::endl;
      }
    } 
    else 
    {
      if (board.turn == 'B') 
      { 
        std::cout << "Black to play: " << std::endl;
      }
      else 
      {
        std::cout << "White to play: " << std::endl;
      }
    }

    print_board(board);
    std::cout << "Legal moves: " << board.legal_moves.size() << std::endl;
    
    AgentInterface& current_agent = *((board.turn == PLAYER1) ? p1a : p2a);
    Move move = current_agent.get_move(board);

    if (!(move.move_bb & board.legal_bb))
    {
      std::cout << "Illegal move. Try again." << std::endl;
      continue;
    }
    
    board = make_move(board, move);

    std::cout << "Move played: " << move.symbol << std::endl;
    std::cout << std::endl;
  }
  
  int p1c = popcount64(board.p1_bb);
  int p2c = popcount64(board.p2_bb);

  std::string result_message = (p1c > p2c) ? "Black has won" : (p2c > p1c) ? "White has won" : "Draw.";
  std::cout << "Game over. " << result_message << std::endl;
  std::cout << "Black: " << p1c << " White: " << p2c << std::endl;

  print_board(board);
}
