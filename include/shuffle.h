#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <obl_primitives_ext.h>
#include "wakson/RecursiveShuffle/RecursiveShuffle.hpp"

namespace obl {
    class OShuffler {
    public:
        OShuffler() {}
        ~OShuffler() {}

        void shuffle(unsigned char *buf, uint64_t N, size_t block_size){
            std::cout << "OShuffler::shuffle" << std::endl;
            RecursiveShuffle_M1(buf, N, block_size);
        };
    };
}