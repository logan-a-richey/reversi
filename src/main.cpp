// legal_move.cpp

#include <iostream>
#include <cstdint>

#include "Board.h"
#include "reversi_utils.h"

int main(){
    /*
    std::cout << "N:" << std::endl;
    print_bb(BORDER_N);
    std::cout << std::endl;

    std::cout << "E:" << std::endl;
    print_bb(BORDER_E);
    std::cout << std::endl;
    
    std::cout << "S:" << std::endl;
    print_bb(BORDER_S);
    std::cout << std::endl;
    
    std::cout << "W:" << std::endl;
    print_bb(BORDER_W);
    std::cout << std::endl;
    */

    Board start_position = get_start_position();
    print_board(start_position);

    return 0;
}

