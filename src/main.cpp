// main.cpp

#include <iostream>
#include "game_manager.h"

int main(int argc, char** argv)
{
  // determine player types
  int p1_t = 0;
  int p2_t = 0;
  switch (argc)
  {
    case 2:
      p1_t = std::atoi(argv[1]);
      break;
    case 3:
      p1_t = std::atoi(argv[1]);
      p2_t = std::atoi(argv[2]);
      break;
    case default:
      break;
  }

  GameManager game;
  game.run(p1_t, p2_t);

  return 0;
}
