// agent_bot_minimax.cpp

// TODO
// implement minimax
// currently, the bot behaves the same as BotRandom.

#include "agent_bot_minimax.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include "board.h"
#include "move.h"
#include "player.h"

AgentBotMinimax::AgentBotMinimax() {
    // engine setup (random move seeding?)
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

Move AgentBotMinimax::get_move(const Board &board) {
    // TODO
    // minimax to eval allmoves in the current `board` state
    // pick an advantageous move out of the set of moves.
    
    int num_moves = board.legal_moves.size();
    if (num_moves == 0) {
        // TODO
        // better way to handle this? 
        // maybe return a "null move" and upstream recognize it is not a legal move;
        // we don't want to "crash" the program if something goes wrong.
        // this is more for debugging.
        std::cerr << "[E] BotMinimax has no legal moves available." << std::endl;
        exit(1);
    }
    unsigned int random_index = std::rand() % num_moves;
    return board.legal_moves[random_index];
}

