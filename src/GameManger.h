// GameManager.h

#include <vector>
#include "Board.h"

class GameManager {
public:
    GameManager() = default;

private:
    std::vector<Board> history;
};
