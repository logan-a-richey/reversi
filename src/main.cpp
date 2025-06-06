// main.cpp

#include <iostream>
#include <cstdint>
#include <memory>

int main(int argc, char** argv)
{
    // Game Loop
    
    /*
    auto game = GameManager();
    auto black_agent = std::make_unique<HumanAgent_Terminal>();
    auto white_agent = std::make_unique<BotAgent_Random>();

    while (!game.is_game_over()) 
    {
        Agent& agent = game.current_player() == 0 ? *black_agent : *white_agent;
        int move = agent.get_move(game.current_state());

        auto legal = game.legal_moves();
        if (std::find(legal.begin(), legal.end(), move) == legal.end()) 
        {
            std::cout << "Illegal move!\n";
            continue;
        }

        game.make_move(move);
        render(game.current_state());  // Print board to terminal
    }
    */

    return 0;
}

