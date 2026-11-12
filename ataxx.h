#ifndef ATAXX_ATAXX_H
#define ATAXX_ATAXX_H
#include <cstdint>
#include <iosfwd>
#include <iostream>
#include <immintrin.h>

namespace Ataxx {
    using u64=uint64_t;
    using u32=uint64_t;
    using u16=uint16_t;
    using u8=uint8_t;
    namespace Utils {
        inline void bitView(const u64 n) {
            for (int i=0;i<64;i++) {
                if (i%8==0){std::cout<<"\n";}
                if (n&1ull<<i){std::cout<<"1";}
                else{std::cout<<"0";}
            }
        }
        inline std::string printNum(const u64 n) {
            std::string num=std::to_string(n);
            int c=1;
            for (int i=static_cast<int>(num.size())-1;i>0;i--) {
                if (c%3==0){num.insert(num.begin()+i,',');}
                c++;
            }
            return num;
        }
    }
    namespace zobrist {
        constexpr u64 zobrist[129]={
            16897820444671774157ULL,13404073877236354975ULL,8590767671267434841ULL,13190510044376467060ULL,11767080589088035672ULL,11756713033010553130ULL,12495449823460033667ULL,990151838476928748ULL,12791616382354445263ULL,
            16848936209290451031ULL,2666895674391514737ULL,12848694513921538892ULL,8941397808853395492ULL,5629446472334450555ULL,13941356135069524350ULL,1747558189842236315ULL,12947232652984294644ULL,
            9552559577164808054ULL,7440965436904214790ULL,861158568372053914ULL,15231974317873868224ULL,1313360661338599457ULL,11444275335866259230ULL,3152288780854007122ULL,15017734060767340203ULL,
            10321677998758484518ULL,17804231897280115463ULL,2581307465998073002ULL,13837397816430736381ULL,5893623333413714220ULL,2635637293607972867ULL,6324362369597008853ULL,955946049832569798ULL,
            3008954550132180703ULL,15547829558799484033ULL,1248027312655243611ULL,9504573624580320343ULL,1050860581698962043ULL,10319817482992315970ULL,1808870861748689834ULL,5949432693755525068ULL,
            6806967208272885734ULL,17658691900724684756ULL,16860956103901803039ULL,7298916139279619918ULL,15321847997545018767ULL,15838528228162218666ULL,5425458916516654957ULL,7978323600683910131ULL,
            1761546392100752106ULL,5807616214727945182ULL,4167360837402763098ULL,10148649990958312661ULL,3387788167948183521ULL,1136075109748865587ULL,10471928271389363635ULL,8997261575034836540ULL,
            14847700828568877687ULL,7826711938595033807ULL,11454128520553271467ULL,8413276569583625076ULL,8814399965497556418ULL,18237633218738538256ULL,6247181170305511931ULL,17328747317993736412ULL,
            2001773908568648176ULL,3904013355388471256ULL,7710658735217726783ULL,9402727726328626019ULL,13015074889109205903ULL,12953505326944237053ULL,18313555744828450716ULL,15629913719311786376ULL,
            7616141698764706585ULL,6471043584678894967ULL,11613588399199324063ULL,9474296912937352905ULL,6511335931385718199ULL,15592630777727423044ULL,17397999222612029937ULL,13975144228261473642ULL,
            6920349162807502372ULL,4863522674477544379ULL,8676324668350355470ULL,36594550891536491ULL,14186775660967206970ULL,8364952741058460644ULL,10850987376489110864ULL,259621580510694717ULL,
            4307109808159074889ULL,10536289367600182839ULL,18414118469738301048ULL,17657084002002984475ULL,2965419950289539757ULL,10054636029791501131ULL,14295918746095283818ULL,14480655392394079321ULL,
            9027463362583344780ULL,11702372062937523860ULL,752650235760042635ULL,16411963685187063746ULL,13587593784633755512ULL,9373382731539881218ULL,1763992721058576758ULL,961622915247601091ULL,
            926214150464721364ULL,8645200965924002409ULL,6306079970198352477ULL,13783934361231425101ULL,13014101463849566357ULL,14240015278534249291ULL,13959727485949873838ULL,12284746134804435192ULL,
            12573658672781861906ULL,6998369002307392645ULL,3631051411543127229ULL,17523365968045481710ULL,17037409277745008143ULL,8395598950129065917ULL,4295029089523244137ULL,312577558893159252ULL,
            16190043774353961989ULL,17072437747565012835ULL,13821471463705682303ULL,5235817128604505476ULL,8905191796560290687ULL,273102322729082879ULL,1241804915178020297ULL,8266326002750202771ULL
        };
    }
    namespace masks {
        constexpr u64 MASKCLOSE[64]={
            0x0000000000000302ULL,0x0000000000000705ULL,0x0000000000000E0AULL,0x0000000000001C14ULL,0x0000000000003828ULL,0x0000000000007050ULL,0x000000000000E0A0ULL,0x000000000000C040ULL,
            0x0000000000030203ULL,0x0000000000070507ULL,0x00000000000E0A0EULL,0x00000000001C141CULL,0x0000000000382838ULL,0x0000000000705070ULL,0x0000000000E0A0E0ULL,0x0000000000C040C0ULL,
            0x0000000003020300ULL,0x0000000007050700ULL,0x000000000E0A0E00ULL,0x000000001C141C00ULL,0x0000000038283800ULL,0x0000000070507000ULL,0x00000000E0A0E000ULL,0x00000000C040C000ULL,
            0x0000000302030000ULL,0x0000000705070000ULL,0x0000000E0A0E0000ULL,0x0000001C141C0000ULL,0x0000003828380000ULL,0x0000007050700000ULL,0x000000E0A0E00000ULL,0x000000C040C00000ULL,
            0x0000030203000000ULL,0x0000070507000000ULL,0x00000E0A0E000000ULL,0x00001C141C000000ULL,0x0000382838000000ULL,0x0000705070000000ULL,0x0000E0A0E0000000ULL,0x0000C040C0000000ULL,
            0x0003020300000000ULL,0x0007050700000000ULL,0x000E0A0E00000000ULL,0x001C141C00000000ULL,0x0038283800000000ULL,0x0070507000000000ULL,0x00E0A0E000000000ULL,0x00C040C000000000ULL,
            0x0302030000000000ULL,0x0705070000000000ULL,0x0E0A0E0000000000ULL,0x1C141C0000000000ULL,0x3828380000000000ULL,0x7050700000000000ULL,0xE0A0E00000000000ULL,0xC040C00000000000ULL,
            0x0203000000000000ULL,0x0507000000000000ULL,0x0A0E000000000000ULL,0x141C000000000000ULL,0x2838000000000000ULL,0x5070000000000000ULL,0xA0E0000000000000ULL,0x40C0000000000000ULL,
        };
        constexpr u64 MASKFAR[64]={
            0x0000000000070404ULL,0x00000000000F0808ULL,0x00000000001F1111ULL,0x00000000003E2222ULL,0x00000000007C4444ULL,0x0000000000F88888ULL,0x0000000000F01010ULL,0x0000000000E02020ULL,
            0x0000000007040404ULL,0x000000000F080808ULL,0x000000001F111111ULL,0x000000003E222222ULL,0x000000007C444444ULL,0x00000000F8888888ULL,0x00000000F0101010ULL,0x00000000E0202020ULL,
            0x0000000704040407ULL,0x0000000F0808080FULL,0x0000001F1111111FULL,0x0000003E2222223EULL,0x0000007C4444447CULL,0x000000F8888888F8ULL,0x000000F0101010F0ULL,0x000000E0202020E0ULL,
            0x0000070404040700ULL,0x00000F0808080F00ULL,0x00001F1111111F00ULL,0x00003E2222223E00ULL,0x00007C4444447C00ULL,0x0000F8888888F800ULL,0x0000F0101010F000ULL,0x0000E0202020E000ULL,
            0x0007040404070000ULL,0x000F0808080F0000ULL,0x001F1111111F0000ULL,0x003E2222223E0000ULL,0x007C4444447C0000ULL,0x00F8888888F80000ULL,0x00F0101010F00000ULL,0x00E0202020E00000ULL,
            0x0704040407000000ULL,0x0F0808080F000000ULL,0x1F1111111F000000ULL,0x3E2222223E000000ULL,0x7C4444447C000000ULL,0xF8888888F8000000ULL,0xF0101010F0000000ULL,0xE0202020E0000000ULL,
            0x0404040700000000ULL,0x0808080F00000000ULL,0x1111111F00000000ULL,0x2222223E00000000ULL,0x4444447C00000000ULL,0x888888F800000000ULL,0x101010F000000000ULL,0x202020E000000000ULL,
            0x0404070000000000ULL,0x08080F0000000000ULL,0x11111F0000000000ULL,0x22223E0000000000ULL,0x44447C0000000000ULL,0x8888F80000000000ULL,0x1010F00000000000ULL,0x2020E00000000000ULL,
        };
        inline u64 neighbours(const u64 b) {
            const u64 mid=(b&0xFEFEFEFEFEFEFEFEULL)>>1|b|(b&0x7F7F7F7F7F7F7F7FULL)<<1;
            return (mid<<8|mid|mid>>8)&~b&0x7F7F7F7F7F7F7FULL;
        }
    }
    class Move {
        u8 _from{};
        u8 _to{};
        u8 _captures{};
    public:
        void setTo(const u8 idx){_to=idx;}
        void setFrom(const u8 idx){_from=idx;}
        void setCaptures(const u64 opp,const u64 mask) {_captures=_pext_u64(opp,mask);}
        [[nodiscard]] u8 to() const{return _to;}
        [[nodiscard]] u8 from() const{return _from;}
        [[nodiscard]] u64 captures(const u64 mask) const {return _pdep_u64(_captures,mask);}
        Move(const u8 from,const u8 to) {
            setFrom(from);
            setTo(to);
        }
        Move(const u8 from,const u8 to,const u64 opp,const u64 mask) {
            setFrom(from);
            setTo(to);
            setCaptures(opp,mask);
        }
        Move()=default;
    };
    class MovePacked {
        u32 data{};
    public:
        void setTo(const u8 idx){data|=idx;}
        void setFrom(const u8 idx){data|=idx<<6;}
        void setCaptures(const u64 opp,const u64 mask) {data|=_pext_u64(opp,mask)<<12;}
        [[nodiscard]] u8 to() const{return data&0x003F;}
        [[nodiscard]] u8 from() const{return (data&0xFC0)>>6;}
        [[nodiscard]] u64 captures(const u64 mask) const {return _pdep_u64(data>>12,mask);}
        MovePacked(const u8 from,const u8 to) {
            setFrom(from);
            setTo(to);
        }
        MovePacked(const u8 from,const u8 to,const u64 opp,const u64 mask) {
            setFrom(from);
            setTo(to);
            setCaptures(opp,mask);
        }
        MovePacked()=default;
    };
    class Board {
        u64 cells[2]{};
        bool _stm{};
    public:
        void _debugPlace(const int idx,const bool stm=false) {cells[stm]|=1ull<<idx;}
        [[nodiscard]] u64 hash() const {
            u64 hash{};
            auto temp=cells[0];
            while (temp) {
                const uint8_t idx=__builtin_ctzll(temp);
                temp&=temp-1;
                hash^=zobrist::zobrist[idx];
            }
            temp=cells[1];
            while (temp) {
                const uint8_t idx=__builtin_ctzll(temp);
                temp&=temp-1;
                hash^=zobrist::zobrist[idx+64];
            }
            return _stm?hash^zobrist::zobrist[128]:hash;
        }
        [[nodiscard]] u64 occ() const {return (cells[0]|cells[1])&0x7F7F7F7F7F7F7FULL;}
        [[nodiscard]] u64 sideOcc(const bool stm) const {return cells[stm]&0x7F7F7F7F7F7F7FULL;}
        [[nodiscard]] bool stm() const{return _stm;}
        void makeMove(const Move move) {
            cells[_stm]^=1ull<<move.from();
            cells[_stm]|=1ull<<move.to();
            const u64 flips=move.captures(masks::MASKCLOSE[move.to()]);
            cells[_stm]|=flips;
            cells[!_stm]^=flips;
            _stm=!_stm;
        }
        void unmakeMove(const Move move) {
            const u64 flips=move.captures(masks::MASKCLOSE[move.to()]);
            _stm=!_stm;
            cells[!_stm]|=flips;
            cells[_stm]^=flips;
            cells[_stm]^=1ull<<move.to();
            cells[_stm]|=1ull<<move.from();
        }
        friend std::ostream &operator<<(std::ostream &os,const Board &pos) {
            for (int i=0;i<56;i++) {
                if (i%8==0&&i){std::cout<<"\n";}
                if ((i+1)%8==0){continue;}
                if (pos.cells[0]&1ull<<i) {std::cout<<"X ";}
                else if (pos.cells[1]&1ull<<i) {std::cout<<"O ";}
                else{std::cout<<"_ ";}
            }
            return os;
        }
    };
    class Movelist {
        Move moves[256]{};
        int _size=0;
    public:
        [[nodiscard]] size_t size() const{return _size;}
        [[nodiscard]] bool empty() const{return _size==0;}
        void add(const Move move) {
            moves[_size]=move;
            _size++;
        }
        void pop() {_size--;}
        void clear() {_size=0;}
        const Move &operator[](const u8 idx) const {return moves[idx];}
    };
    namespace movegen {
        template <bool jmpMoves>
        void genMoves(const Board &pos,Movelist &moves,const u64 opp) {
            if constexpr (!jmpMoves) {
                u64 dest=masks::neighbours(pos.sideOcc(pos.stm()))&~pos.sideOcc(!pos.stm());
                while (dest) {
                    const u8 idx=__builtin_ctzll(dest);
                    dest&=dest-1;
                    moves.add(Move(55,idx,opp,masks::MASKCLOSE[idx]));
                }
            }
            else {
                u64 pieces=pos.sideOcc(pos.stm());
                while (pieces) {
                    const u8 from=__builtin_ctzll(pieces);
                    pieces&=pieces-1;
                    u64 dest=masks::MASKFAR[from]&0x7F7F7F7F7F7F7FULL&~pos.occ();
                    while (dest) {
                        const u8 idx=__builtin_ctzll(dest);
                        dest&=dest-1;
                        moves.add(Move(from,idx,opp,masks::MASKCLOSE[idx]));
                    }
                }
            }
        }
        inline void legalMoves(const Board &pos,Movelist &moves) {
            const u64 opp=pos.sideOcc(!pos.stm());
            genMoves<false>(pos,moves,opp);
            genMoves<true>(pos,moves,opp);
        }
        template <bool jmpMoves>
        u8 _countMoves(const Board &pos) {
            u8 moveCount=0;
            if constexpr (!jmpMoves) {
                const u64 dest=masks::neighbours(pos.sideOcc(pos.stm()))&0x7F7F7F7F7F7F7FULL&~pos.sideOcc(!pos.stm());
                moveCount+=__builtin_popcountll(dest);
            }
            else {
                u64 pieces=pos.sideOcc(pos.stm());
                while (pieces) {
                    const u8 from=__builtin_ctzll(pieces);
                    pieces&=pieces-1;
                    const u64 dest=masks::MASKFAR[from]&0x7F7F7F7F7F7F7FULL&~pos.occ();
                    moveCount+=__builtin_popcountll(dest);
                }
            }
            return moveCount;
        }
        inline u8 countMoves(const Board &pos) {
            return _countMoves<false>(pos)+_countMoves<true>(pos);
        }
    }
}





#endif //ATAXX_ATAXX_H
