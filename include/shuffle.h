#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "wakson/RecursiveShuffle/RecursiveShuffle.hpp"

namespace obl {
    class OShuffler {
    public:
        OShuffler() {}
        ~OShuffler() {}

        void shuffle(unsigned char *buf, uint64_t N, size_t block_size){
            RecursiveShuffle_M1(buf, N, block_size);
        };
    };
}