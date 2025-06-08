// GameManager.cpp

#include <cstdint>
#include <memory>
#include <vector>

#include "agents/AgentFactory.h"
#include "agents/IAgent.h"
#include "core/Board.h"
#include "core/reversi_utils.h"
#include "core/GameManager.h"

GameManager::GameManager(int _p1_type, int _p2_type) 
    : p1_type(_p1_type), p2_type(_p2_type) {}

void GameManager::run()
{
    Board board = Reversi::get_start_position();
    history.clear();
    history.push_back(board);

    std::unique_ptr<IAgent> black_agent = create_agent(p1_type);
    std::unique_ptr<IAgent> white_agent = create_agent(p2_type);

    // --- Game Loop ---
    while (!board.is_game_over)
    {
        // Terminal turn message:
        if (board.is_skipped)
        {
            if (board.turn == 'B')
                std::cout << "White turn skipped. Black to play: " << std::endl;
            else
                std::cout << "Black turn skipped. White to play: " << std::endl;
        }
        else
        {
            if (board.turn == 'B')
                std::cout << "Black to play: " << std::endl;
            else
                std::cout << "White to play: " << std::endl;
        }
        Reversi::print_board(board);

        // Prompt the correct Agent to play mpve
        IAgent &current_agent = *((board.turn == 'B') ? black_agent : white_agent);
        uint64_t move = current_agent.get_move(board);

        if (!(move & board.legal))
        {
            std::cout << "Illegal move. Try again." << std::endl;
            continue;
        }

        // Make move and update board, history
        board = Reversi::make_move(board, move);
        history.push_back(board);

        std::cout << "Move played: " << Reversi::get_str_move(move) << std::endl;
        std::cout << std::endl;
    }

    // --- Game Over ---
    int black_count = Reversi::popcount64(board.black);
    int white_count = Reversi::popcount64(board.white);
    
    std::string result_message = 
          (black_count > white_count) ? "Black has won."
        : (black_count < white_count) ? "White has won."
        : "Draw.";

    std::cout << "Game over. " << result_message << std::endl;
    std::cout << "Black: " << black_count << " White: " << white_count << std::endl;
    Reversi::print_board(board);
}

