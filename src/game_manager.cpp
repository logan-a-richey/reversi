// game_manager.cpp

#include "game_manager.h"
#include "agent_factory.h"

void GameManager::run(int p1_t, int p2_t)
{
  std::cout << "Playing game." << std::endl;
  
  auto p1a = create_agent(p1_t); 
  auto p2a = create_agent(p2_t);

}
