// legal_move.cpp

#include <iostream>
#include <iomanip>
#include <cstdint>

#include "Board.h"
#include "reversi_utils.h"


int main(){
    
    GameManager game;

    Board start_position = get_start_position();
    print_board(start_position);
    
    uint64_t move = 0x0000100000000000ULL;
    std::cout << "made move: 0x" << std::hex << std::setw(16) << std::setfill('0') << move << std::endl;

    Board new_pos = make_move(start_position, move);
    print_board(new_pos);
    return 0;
}

