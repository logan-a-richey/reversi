// main.cpp

#include <cstdint>
#include <iostream>
#include <string>

#include "game_manager.h"
#include "reversi_utils.h"

/*****************************************************************************/
void test_str_and_bb() {
  uint64_t bb_move = 0;

  while (true) {
    std::cout << "Input a string move (a2): ";
    std::string str_move;
    std::cin >> str_move;
    std::cout << std::endl;

    bb_move = str_to_bb(str_move);
    print_bb(bb_move);

    std::cout << "Input a bitboard move: ";
    std::cin >> bb_move;
    std::cout << std::endl;

    str_move = bb_to_str(bb_move);
    std::cout << str_move << std::endl;
  }
}

/*****************************************************************************/
int main(int argc, char **argv) {
  // determine player types
  int p1_t = 0;
  int p2_t = 0;
  switch (argc) {
    case 2:
      p1_t = std::atoi(argv[1]);
      break;
    case 3:
      p1_t = std::atoi(argv[1]);
      p2_t = std::atoi(argv[2]);
      break;
    default:
      break;
  }

  GameManager game;
  game.run(p1_t, p2_t);

  // test_str_and_bb();

  return 0;
}
