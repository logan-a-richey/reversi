// legal_move.cpp

#include <iostream>
#include <iomanip>
#include <sstream>

#include <cstdint>
#include <memory>

#include "Board.h"
#include "reversi_utils.h"
#include "IAgent.h"
#include "AgentFactory.h"

void simple_test()
{
    Board start_position = get_start_position();
    print_board(start_position);
    
    uint64_t move = 0x0000100000000000ULL;
    std::cout << "made move: 0x" 
        << std::hex << std::setw(16) << std::setfill('0') << move << std::endl;

    Board new_pos = make_move(start_position, move);
    print_board(new_pos);
}

int main(int argc, char** argv)
{
    // --- Cmdline Args ---
    if (argc != 3)
    {
        std::cerr 
            << "[USAGE] ./main <player1type> <player2type>\n"
            << "  0 = human terminal\n"
            << "  1 = random bot\n"
            << "  2 = minimax bot\n"
            << std::endl;
        return 1;
    }

    // --- Game Setup ---
    int p1_type = std::atoi(argv[1]);
    int p2_type = std::atoi(argv[2]);
   
    // TODO - abstract game logic away into GameManager
    // auto game = GameManager();
    Board board = get_start_position();

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
        
        IAgent& current_agent = *(board.turn == 'B' ? black_agent : white_agent);
        uint64_t move = current_agent.get_move(board);

        if (!(move & board.legal))
        {
            std::cout << "Illegal move. Try again." << std::endl;
            continue;
        }
        
        std::cout << "Move played: " << get_str_move(move) << std::endl;  
        std::cout << std::endl;

        board = make_move(board, move);
    }
    
    // --- Game Over ---
    std::vector<int> count = get_piece_count(board);
    std::string result_message = (count[0] > count[1]) ? "Black has won." : (count[0] < count[1]) ? "White has won." : "Draw.";
    
    std::cout << "Game over. " << result_message << std::endl;
    std::cout << "Black: " << count[0] << " White: " << count[1] << std::endl;
    print_board(board);

    return 0;
}

