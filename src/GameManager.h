// GameManager.h

#pragma once

#include <iostream>
#include <sstream>
#include <vector>

#include "Board.h"

class GameManager
{
  public:
    int p1_type;
    int p2_type;
    std::vector<Board> history;

    GameManager(int p1_type, int p2_type);
    void run();
};
