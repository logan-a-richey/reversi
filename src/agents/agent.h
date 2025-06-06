// agent.h
// interface for other agents

#include <cstdint>
typedef uint64_t u64;

class Board;

class Agent
{
public:
    virtual ~Agent() = default;
    virtual u64 get_move(const Board& board) = 0;
};

