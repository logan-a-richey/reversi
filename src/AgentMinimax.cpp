/******************************************************************************/
// AgentMinimax.cpp

#include <limits>
#include <cstdint>

#include "AgentMinimax.h"
#include "Board.h"
#include "reversi_utils.h"

// --- Private ---
int AgentMinimax::evaluate(const Board& board)
{
    if (board.is_game_over) {
        auto count = get_piece_count(board);
        int diff = count[0] - count[1]; // Black - White
        return (board.turn == 'B') ? diff * 1000 : -diff * 1000;
    }

    int mobility_score = 0;
    for (int i = 0; i < 64; ++i)
        if ((1ULL << i) & board.legal)
            mobility_score++;

    return mobility_score;
}

int AgentMinimax::minimax(const Board& board, int depth, int alpha, int beta)
{
    if (depth == 0 || board.is_game_over)
        return evaluate(board);

    int best = std::numeric_limits<int>::min();

    for (int i = 0; i < 64; ++i)
    {
        uint64_t move = 1ULL << i;
        if (!(move & board.legal)) continue;

        Board child = make_move(board, move);
        int score = -minimax(child, depth - 1, -beta, -alpha); // Negamax

        best = std::max(best, score);
        alpha = std::max(alpha, score);
        if (alpha >= beta) break;
    }

    return best;
}

// --- Public ---
uint64_t AgentMinimax::get_move(const Board& board)
{
    static const int depth = 7;

    uint64_t best_move = 0ULL;

    int best_score = std::numeric_limits<int>::min();

    for (int i = 0; i < 64; ++i)
    {
        uint64_t move = 1ULL << i;
        if (!(move & board.legal)) continue;

        Board child = make_move(board, move);
        int score = -minimax(
            child, 
            depth, 
            std::numeric_limits<int>::min(), 
            std::numeric_limits<int>::max()
        );

        if (score > best_score) {
            best_score = score;
            best_move = move;
        }
    }

    return best_move;
}

