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
    std::cout<<pos<<"\n";
    for (int d=0;d<=10;d++) {
        auto t0=std::chrono::high_resolution_clock::now();
        uint64_t nodes=perft(pos,d);
        auto t1=std::chrono::high_resolution_clock::now();
        int time=std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count();
        std::cout<<"Depth "<<d<<" nodes "<<nodes<<" time "<<time<<"ms nps "<<nodes/(time?time:1)*(time?1000:1)<<"\n";
    }



    return 0;
}
