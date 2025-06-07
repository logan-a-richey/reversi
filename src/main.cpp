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
    if (argc != 3)
    {
        std::cerr 
            << "[USAGE] ./main <player1type> <player2type>\n"
            << "  0 = human terminal\n"
            << "  1 = random bot"
            << std::endl;
        return 1;
    }

    // TODO - do with string streams
    int p1_type = std::atoi(argv[1]);
    int p2_type = std::atoi(argv[2]);
   
    // TODO - abstract game logic away into GameManager
    // auto game = GameManager();
    Board board = get_start_position();

    std::unique_ptr<IAgent> black_agent = create_agent(p1_type);
    std::unique_ptr<IAgent> white_agent = create_agent(p2_type);
    
    bool game_over = false;
    bool black_passed = false;
    bool white_passed = false;

    while(!game_over)
    {
        std::cout << std::endl;
        std::string msg = (board.turn == 'B') ? "Black" : "White";
       
        if (board.legal == 0)
        {
            std::cout << msg << " has no legal moves. Passing turn." << std::endl;
            if (board.turn == 'B')
            {
                black_passed = true;
                board.turn = 'W';
            }
            else 
            {
                white_passed = true;
                board.turn = 'B';
            }

            // end game if both players have been passed
            if (black_passed && white_passed)
            {
                game_over = true;
                // break;
            }

            board.legal = get_legal_moves(board);
            continue;
        }

        // Reset Player passed
        black_passed = (board.turn == 'B') ? false : black_passed;
        white_passed = (board.turn == 'W') ? false : white_passed;
        
        // Terminal turn message:
        std::cout << "Turn: " <<  msg << std::endl;
        print_board(board);
        
        auto& current_agent = (board.turn == 'B') ? black_agent : white_agent;
        
        uint64_t move = current_agent->get_move(board);
        
        if (!(move & board.legal))
        {
            std::cout << "Illegal move. Try again." << std::endl;
            continue;
        }
        
        board = make_move(board, move);
        board.legal = get_legal_moves(board);
    }
    
    // Print final position
    std::vector<int> count = get_piece_count(board);
    
    std::string result_message = 
          (count[0] > count[1]) ? "Black has won."
        : (count[0] < count[1]) ? "White has won."
        : "Draw.";
    
    std::cout << std::endl;
    std::cout << "Game over. " << result_message << std::endl;
    std::cout << "Black: " << count[0] << " White: " << count[1] << std::endl;
    print_board(board);

    return 0;
}

