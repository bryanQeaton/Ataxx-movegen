#ifndef ATAXX_PERFT_H
#define ATAXX_PERFT_H
#include "ataxx.h"


inline uint64_t perft(Ataxx::Board &pos,const int depth) {
    if (depth==0){return 1ull;}
    if (depth==1) {
        return Ataxx::movegen::countMoves(pos);
    }
    auto moves=Ataxx::Movelist();
    Ataxx::movegen::legalMoves(pos,moves);
    uint64_t nodes=0ull;
    for (int m=0;m<moves.size();m++) {
        pos.makeMove(moves[m]);
        nodes+=perft(pos,depth-1);
        pos.unmakeMove(moves[m]);
    }

    return nodes;
}


#endif //ATAXX_PERFT_H
