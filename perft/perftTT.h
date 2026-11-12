#ifndef ATAXX_PERFTTT_H
#define ATAXX_PERFTTT_H
#include <chrono>

#include "../src/ataxx.h"


inline uint32_t key(const uint64_t hash){return hash>>32;}
struct Entry {
    uint32_t key=0;
    uint8_t depth=0;
    uint64_t nodes=0;
};

struct Bucket { alignas(64)
    Entry entries[4]{};
};
class TT {
    std::vector<Bucket> table;
    size_t TTSIZE{};

public:
    Entry *probe(const uint64_t hash) {
        Entry *empty=nullptr;
        Entry *lowest=nullptr;
        auto &bucket=table[hash%TTSIZE];
        for (int i=0;i<4;i++) {
            if (bucket.entries[i].key==key(hash)) {return &bucket.entries[i];}
            if (lowest==nullptr||bucket.entries[i].depth<lowest->depth) {lowest=&bucket.entries[i];}
            else if (bucket.entries[i].key==0) {empty=&bucket.entries[i];}
        }
        if (empty!=nullptr){return empty;}
        return lowest;
    }
    void clear() {
        for (auto &bucket:table) {
            for (int i=0;i<4;i++) {
                bucket.entries[i]=Entry();
            }
        }
    }
    void prefetch(const uint64_t hash) const {
        __builtin_prefetch(&table[hash%TTSIZE],0,1);
    }
    explicit TT(const size_t mb) {
        TTSIZE=mb*1024ull*1024ull/sizeof(Bucket);
        table.resize(TTSIZE);
    }
};
inline auto tt=TT(512);
inline uint64_t perftTT(Ataxx::Board &pos,const int depth) {
    if (depth==0){return 1ull;}
    if (depth==1) {
        return Ataxx::movegen::countMoves(pos);
    }
    const uint64_t hash=pos.hash();
    tt.prefetch(hash);
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
inline void runperft() {
    auto pos=Ataxx::Board();
    pos._debugPlace(0);
    pos._debugPlace(6,true);
    pos._debugPlace(54);
    pos._debugPlace(48,true);
    std::cout<<pos<<"\n";
    for (int d=0;d<=10;d++) {
        auto t0=std::chrono::high_resolution_clock::now();
        uint64_t nodes=perftTT(pos,d);
        auto t1=std::chrono::high_resolution_clock::now();
        int time=std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count();
        std::cout<<"Depth "<<d<<" nodes "<<Ataxx::Utils::printNum(nodes)<<" time "<<time<<"ms nps "<<Ataxx::Utils::printNum(nodes/(time?time:1)*(time?1000:1))<<"\n";
    }
}

#endif //ATAXX_PERFTTT_H
