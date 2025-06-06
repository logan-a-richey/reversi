// AgentHumanTerminal.h

#include <iostream>
#include <cstdint>
#include <string>
#include <regex>

#include "agent.h"

class Board;

class AgentHumanTerminal : public Agent
{
public:
    uint64_t get_move(const Board& board) override
    {
        static std::regex pattern("^[a-h][1-8]$");
        while (true)
        {
            std::string str_move;

            if (board.turn == 'b') 
                std::cout << "Black to move: ";
            else 
                std::cout << "White to move: ";

            std::cin >> str_move;
            
            if (!(std::regex_match(str_move, pattern)))
            {
                std::cout << "Regex failed. Expected format like 'a1' or 'h8'." << std::endl;
                continue;
            }
        
            uint64_t int_move = parse_move(str_move);
            
            if (!(int_move & board.legal))
            {
                std::cout << "That is not a legal move. Try again." << std::endl;
                continue;
            }
            
            return int_move
        }
    }

private: 
    uint64_t parse_move(const std::string& str_move)
    {
        char file = str_move[0];
        char rank = str_move[1];

        int col = file - 'a';
        int row = rank - '1';

        int bit_index = row * 8 + col;

        uint64_t int_move = 1ULL << bit_index;
        return int_move;
    }
};

