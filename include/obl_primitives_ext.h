#pragma once

#include "obl_primitives.h"

inline void oswap(uint8_t *block1, uint8_t *block2, size_t block_size, bool swap_flag){
    if(swap_flag){
        for(size_t i=0; i<block_size; i++){
            uint8_t temp = block1[i];
            block1[i] = block2[i];
            block2[i] = temp;
        }
    }
}