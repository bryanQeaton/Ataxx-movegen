#include "src/ataxx.h"

int main() {
    auto pos=Ataxx::Board();

    pos.setFen("x5o/7/7/7/7/7/o5x x 0 1");
    std::cout<<pos;
    std::cout<<pos.getFen();


    return 0;
}
