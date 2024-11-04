#pragma once

#include "obl_primitives.h"

// A size-templated version of oblivious greater than for wide-key Bitonic Sort
// Returns 1 if (*key1p) > (*key2p), and 0 otherwise, in a fully oblivious manner.
template<typename keytype>
inline bool ogt(const keytype *key1p, const keytype *key2p){
    return (*key1p) > (*key2p);
}

inline void oswap(uint8_t *block1, uint8_t *block2, size_t block_size, bool swap_flag){
    if(swap_flag){
        for(size_t i=0; i<block_size; i++){
            uint8_t temp = block1[i];
            block1[i] = block2[i];
            block2[i] = temp;
        }
    }
}