// game_manager.cpp

#include <iostream>

#include "reversi_utils.h"
#include "game_manager.h"
#include "agent_factory.h"

void GameManager::run(int p1_t, int p2_t)
{
  std::cout << "Playing game." << std::endl;
    
  std::unique_ptr<AgentInterface> p1a = create_agent(p1_t); 
  std::unique_ptr<AgentInterface> p2a = create_agent(p2_t);

  Board board = get_start_position();
  init_board_state(board);

  print_board(board);
  std::cout << "Legal moves: " << board.legal_moves.size() << std::endl;
}
