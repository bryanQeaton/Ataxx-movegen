#ifndef ATAXX_PERFT_H
#define ATAXX_PERFT_H
#include "ataxx.h"


inline uint64_t perft(const Ataxx::Board &pos,const int depth) {
    auto moves=Ataxx::Movelist();
    Ataxx::movegen::legalMoves(pos,moves);
    if (depth==0){return 1ull;}
    if (depth==1) {
        return moves.size();
    }
    uint64_t nodes=0ull;
    for (int m=0;m<moves.size();m++) {
        auto newpos=pos;
        newpos.makeMove(moves[m]);
        nodes+=perft(newpos,depth-1);
    }

    return nodes;
}


#endif //ATAXX_PERFT_H
