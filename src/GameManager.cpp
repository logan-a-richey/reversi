// GameManager.cpp
#include "GameManager.h"

#include <cstdint>
#include <memory>
#include <vector>

#include "AgentFactory.h"
#include "IAgent.h"
#include "Board.h"
#include "reversi_utils.h"

GameManager::GameManager(int _p1_type, int _p2_type) : p1_type(_p1_type), p2_type(_p2_type) {}

void GameManager::run()
{
    Board board = get_start_position();
    history.clear();
    history.push_back(board);

    std::unique_ptr<IAgent> black_agent = create_agent(p1_type);
    std::unique_ptr<IAgent> white_agent = create_agent(p2_type);
    
    // --- Game Loop ---
    while(!board.is_game_over)
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
        print_board(board);
        
        // Prompt the correct Agent to play mpve
        IAgent& current_agent = *((board.turn == 'B') ? black_agent : white_agent);
        uint64_t move = current_agent.get_move(board);

        if (!(move & board.legal))
        {
            std::cout << "Illegal move. Try again." << std::endl;
            continue;
        }
        
        // Make move and update board, history
        board = make_move(board, move);
        history.push_back(board);
        
        std::cout << "Move played: " << get_str_move(move) << std::endl;  
        std::cout << std::endl;
    }
    
    // --- Game Over ---
    std::vector<int> count = get_piece_count(board);
    std::string result_message = 
          (count[0] > count[1]) ? "Black has won." 
        : (count[0] < count[1]) ? "White has won." 
        : "Draw.";
    
    std::cout << "Game over. " << result_message << std::endl;
    std::cout << "Black: " << count[0] << " White: " << count[1] << std::endl;
    print_board(board);
}

