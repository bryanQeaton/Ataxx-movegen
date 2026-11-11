#ifndef ATAXX_PERFTTT_H
#define ATAXX_PERFTTT_H
#include "ataxx.h"


constexpr size_t TTSIZEMB=128;
inline uint32_t key(const uint64_t hash){return hash>>32;}
struct Entry {
    uint32_t key=0;
    uint8_t depth=0;
    uint64_t nodes=0;
};
constexpr size_t TTSIZE=TTSIZEMB*1024ull*1024ull/sizeof(Entry);
class TT {
    Entry table[TTSIZE]{};
public:
    Entry *probe(const uint64_t hash) {return &table[hash%TTSIZE];}
};
inline auto tt=TT();
inline uint64_t perftTT(Ataxx::Board &pos,const int depth) {
    if (depth==0){return 1ull;}
    if (depth==1) {
        return Ataxx::movegen::countMoves(pos);
    }
    const uint64_t hash=pos.hash();
    Entry *entry=tt.probe(hash);
    if (entry->key==key(hash)&&entry->depth==depth){return entry->nodes;}

    auto moves=Ataxx::Movelist();
    Ataxx::movegen::legalMoves(pos,moves);
    uint64_t nodes=0ull;
    for (int m=0;m<moves.size();m++) {
        pos.makeMove(moves[m]);
        nodes+=perftTT(pos,depth-1);
        pos.unmakeMove(moves[m]);
    }
    entry->key=key(hash);
    entry->depth=depth;
    entry->nodes=nodes;
    return nodes;
}


#endif //ATAXX_PERFTTT_H
