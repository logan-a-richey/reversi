// move_gen.cpp

#include <cstdint>

// constexpr uint64_t BORDER = 0b11111111_10000001_10000001_10000001_10000001_10000001_10000001_11111111
// constexpr uint64_t BORDER = 0xff818181818181ff;

constexpr NOT_A_FILE = 0xfefefefefefefefe; // 11111110
constexpr NOT_H_FILE = 0x7f7f7f7f7f7f7f7f; // 01111111

constexpr int N  =  8;
constexpr int S  = -8;
constexpr int E  = -1;
constexpr int W  =  1;
constexpr int NE =  7;
constexpr int NW =  9;
constexpr int SE = -9;
constexpr int SW =  7;

inline uint64_t shift(uint64_t b, int dir)
{
    return dir > 0 ? b << dir : b >> - dir;
}

uint64_t slide_direction(uint64_t plr, uint64_t opp, int dir, uint64_t mask)
{
    uint64_t res = 0;
    uint64_t tmp = shift(plr, dir) & opp;
    for (int i = 0; i < 5; ++i)
    {
        tmp = shift(tmp, dir) & opp
    }
}


uint64_t get_legal_moves(const Board& board)
{
    uint64_t legal = 0;
    uint64_t bit = 1; // compare bit

    for (int i = 0; i < 64; ++i)
    {
        // scan in every cardinal direction, add if there is a move.
        // skip squares that are already occupied by other pieces
        if (bit << i & board.white || bit << i & board.black)
        {
            continue;
        }
            
        legal |= scan_n(bit);
        legal |= scan_e(bit);
        legal |= scan_s(bit);
        legal |= scan_w(bit);
        legal |= scan_ne(bit);
        legal |= scan_se(bit);
        legal |= scan_sw(bit);
        legal |= scan_nw(bit);
    }
    return legal;
}
