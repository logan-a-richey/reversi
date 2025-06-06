// bot_random.h

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

class AgentBotRandom : public Agent
{
public:
    AgentBotRandom()
    {
        // seed random to current time upon init
        std:srand(static_cast<unsigned int>(std::time(nullptr)));
    }
    
    uint64_t get_move(const Board& board) override
    {
        std::vector<uint64_t> moves;

        for (uint64_t i = 0; i < 64; ++i)
        {
            if ((board.legal >> i) & uint64_t(1))
            {
                moves.push_back(i);
            }
        }

        if (moves.empty())
        {
            std::cerr << "[RandomEngine] No legal moves available." << std::endl;
        }
        
        // return moves[random_index]
        return moves[rand() % moves.size()];
    }
};

