/******************************************************************************/
// AgentMinimax.cpp

#include <cstdint>
#include <limits>

#include "AgentMinimax.h"
#include "Board.h"
#include "reversi_utils.h"

static const int tile_weights[64] = {
    100, -20, 10,  5,  5, 10, -20, 100,
    -20, -50, -2, -2, -2, -2, -50, -20,
     10,  -2,  5,  1,  1,  5,  -2,  10,
      5,  -2,  1,  0,  0,  1,  -2,   5,
      5,  -2,  1,  0,  0,  1,  -2,   5,
     10,  -2,  5,  1,  1,  5,  -2,  10,
    -20, -50, -2, -2, -2, -2, -50, -20,
    100, -20, 10,  5,  5, 10, -20, 100
};

// --- Private ---
int AgentMinimax::evaluate(const Board &board)
{
    if (board.is_game_over)
    {
        int black_count = popcount64(board.black);
        int white_count = popcount64(board.white);

        int diff = black_count - white_count; // Black - White
        return (board.turn == 'B') ? diff * 1000 : -diff * 1000;
    }

    int mobility_score = 0;
    for (int i = 0; i < 64; ++i)
    {
        if ((1ULL << i) & board.legal)
            mobility_score++;
    }

    return mobility_score;
}

int AgentMinimax::minimax(const Board &board, int depth, int alpha, int beta)
{
    if (depth == 0 || board.is_game_over)
        return evaluate(board);

    int best = std::numeric_limits<int>::min();

    for (int i = 0; i < 64; ++i)
    {
        uint64_t move = 1ULL << i;
        if (!(move & board.legal))
            continue;

        Board child = make_move(board, move);
        int score = -minimax(child, depth - 1, -beta, -alpha); // Negamax

        best = std::max(best, score);
        alpha = std::max(alpha, score);
        if (alpha >= beta)
            break;
    }

    return best;
}

// --- Public ---
uint64_t AgentMinimax::get_move(const Board &board)
{
    static const int depth = 7;

    uint64_t best_move = 0ULL;

    int best_score = std::numeric_limits<int>::min();

    for (int i = 0; i < 64; ++i)
    {
        uint64_t move = 1ULL << i;
        if (!(move & board.legal))
            continue;

        Board child = make_move(board, move);
        int score = -minimax(child, depth, std::numeric_limits<int>::min(),
                             std::numeric_limits<int>::max());

        if (score > best_score)
        {
            best_score = score;
            best_move = move;
        }
    }

    return best_move;
}
