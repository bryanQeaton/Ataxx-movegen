#ifndef ATAXX_PERFT_H
#define ATAXX_PERFT_H
#include "../src/ataxx.h"


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
inline void runperft() {
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
        std::cout<<"Depth "<<d<<" nodes "<<Ataxx::Utils::printNum(nodes)<<" time "<<time<<"ms nps "<<Ataxx::Utils::printNum(nodes/(time?time:1)*(time?1000:1))<<"\n";
    }
}
//pointless no gain
// inline uint64_t perft(Ataxx::Board &pos,const int depth) {
//     if (depth==0){return 1ull;}
//     if (depth==1) {
//         return Ataxx::movegen::countMoves(pos);
//     }
//     uint64_t nodes=0ull;
//     const uint64_t opp=pos.sideOcc(!pos.stm());
//     uint64_t dest=Ataxx::masks::neighbours(pos.sideOcc(pos.stm()))&~pos.sideOcc(!pos.stm());
//     while (dest) {
//         const uint8_t idx=__builtin_ctzll(dest);
//         dest&=(dest-1);
//         const auto move=Ataxx::Move(55,idx,opp, Ataxx::masks::MASKCLOSE[idx]);
//         pos.makeMove(move);
//         nodes+=perft(pos,depth-1);
//         pos.unmakeMove(move);
//     }
//     uint64_t pieces=pos.sideOcc(pos.stm());
//     while (pieces) {
//         const uint8_t from=__builtin_ctzll(pieces);
//         pieces&=(pieces-1);
//         uint64_t dest=Ataxx::masks::MASKFAR[from]&0x7F7F7F7F7F7F7FULL&~pos.occ();
//         while (dest) {
//             const uint8_t idx=__builtin_ctzll(dest);
//             dest&=(dest-1);
//             const auto move=Ataxx::Move(from,idx,opp, Ataxx::masks::MASKCLOSE[idx]);
//             pos.makeMove(move);
//             nodes+=perft(pos,depth-1);
//             pos.unmakeMove(move);
//         }
//     }
//     return nodes;
// }


#endif //ATAXX_PERFT_H
