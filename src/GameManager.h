// GameManager.h

#include <cstdint>
#include <vector>

#include "Board.h"

typedef uint64_t u64;

// class Board;
class PieceCount;

class GameManager 
{
public:
    // RAII
    GameManager();
    ~GameMagner() = default;
    
    // Methods
    const Board& get_current_board() const;
    
    Board make_move(const Board& board, u64 move);
    
    PieceCount get_piece_count(const Board& board);    

private:
    std::vector<Board> history;
};

