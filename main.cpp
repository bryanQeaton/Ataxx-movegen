#include <chrono>
#include <iostream>

#include "ataxx.h"
#include <cstdint>

#include "perft.h"
using u64 = std::uint64_t;



int main() {
    auto pos=Ataxx::Board();
    pos._debugPlace(0);
    pos._debugPlace(6,true);
    pos._debugPlace(54);
    pos._debugPlace(48,true);
    // pos._debugPlace(18);
    // pos._debugPlace(21,true);

    auto moves=Ataxx::Movelist();
    Ataxx::movegen::legalMoves(pos,moves);
    pos.makeMove(moves[16]);


    std::cout<<pos<<"\n";

    for (int m=0;m<moves.size();m++) {
        std::cout<<moves[m].from()<<" "<<moves[m].to()<<" "<<m<<"\n";
    }

    for (int d=0;d<=10;d++) {
        auto t0=std::chrono::high_resolution_clock::now();
        uint64_t nodes=perft(pos,d);
        auto t1=std::chrono::high_resolution_clock::now();
        int time=std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count();
        std::cout<<nodes<<" nodes ";
        std::cout<<time<<" ms ";
        std::cout<<nodes/(time?time:1)*(time?1000:1)<<" nodes per s\n";
    }



    return 0;
}
