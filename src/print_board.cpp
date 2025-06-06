// print_board

#include <iostream>
#include <cstdint>

#include "Board.h"

void print_board(const Board& board)
    int it = 0;
    for (int i = 0; i < 64, ++i)
    {
        if (it % 8 == 0 && it != 0)
            std::cout << "\n"
        it++;

        uint64_t shift = uint64_t(1) << j + i * 8;
        if (shift & board.white) {
            std::cout << "W ";
        } else if (shift & board.black) {
            std::cout << "B ";
        } else if (shift & board.legal) {
            std::cout << "* "; 
        } else {
            std::cout << ". ";
        }
    }
}

