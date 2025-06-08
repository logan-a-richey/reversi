// GameManager.h

#pragma once

#include <iostream>
#include <sstream>
#include <vector>

#include "core/Board.h"

class GameManager
{
  public:
    GameManager(int _p1_type, int _p2_type);
    
    int p1_type;
    int p2_type;
    std::vector<Board> history;

    void run();
};
