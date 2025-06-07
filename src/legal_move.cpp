// legal_move.cpp

#include <iostream>
#include <cstdint>

using u64 = uint64_t;

constexpr u64 BORDER_N = 0x00000000000000ff;
constexpr u64 BORDER_S = 0xff00000000000000;
constexpr u64 BORDER_E = 0x8080808080808080;
constexpr u64 BORDER_W = 0x0101010101010101;

void print_bb(uint64_t bb)
{
    uint64_t bit = 1;
    int it = 0;
    for (int i = 0; i < 64; ++i)
    {
        if (i % 8 == 0 && i != 0) {
            std::cout << "\n";
        }
        if (bit << i & bb) {
            std::cout << "x ";
        } else {
            std::cout << ". ";
        }
        it++;
    }
    std::cout << std::endl;
}

int main(){
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

    return 0;
}

