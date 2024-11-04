#include "sorter.h"
#include <utils.h>

namespace obl {

    // 递归进行双调排序
    template<typename KeyType>
    void BitonicSorter<KeyType>::bitonicMerge(unsigned char *buffer, size_t N, bool ascend) {
        size_t block_size = sizeof(KeyType);
        if(N<2){
            return;
        }
        else if((N & (N * -1))!=N) {
            size_t M = pow2_lt(N);
            unsigned char *block1 = buffer;
            unsigned char *block2 = buffer + (M * block_size); 
            size_t feasible_swaps = N - M;

            for(size_t i=0; i<feasible_swaps; i++) {
                uint8_t swap_flag = ogt<KeyType>((KeyType*)block1, (KeyType*)block2);
                if(ascend){
                    oswap(block1, block2, block_size, swap_flag);
                } else {
                    oswap(block1, block2, block_size, !swap_flag);
                }
                block1+=block_size;
                block2+=block_size; 
            }
        
            bitonicMerge(buffer, M,  ascend);
            bitonicMerge(buffer + (M * block_size), N-M, ascend);
        } 
        else{ //Power of 2 case
            size_t split = N/2;
            unsigned char *block1 = buffer;
            unsigned char *block2 = buffer + (split * block_size); 
            
            for(size_t i=0; i<split; i++) {
                uint8_t swap_flag = ogt<KeyType>((KeyType*)block1, (KeyType*)block2);
                if(ascend){
                    oswap(block1, block2, block_size, swap_flag);
                } else {
                    oswap(block1, block2, block_size, !swap_flag);
                }
                block1+=block_size;
                block2+=block_size; 
            } 

            bitonicMerge(buffer, split, ascend);
            bitonicMerge(buffer + (split * block_size), split,  ascend);
        }
    }

    // 双调排序算法
    template<typename KeyType>
    void BitonicSorter<KeyType>::bitonicSort(unsigned char *buffer, size_t N, bool ascend) {
        size_t block_size = sizeof(KeyType);
        if(N < 2){
            return;
        }
        else {  // Handle non-power of 2 case:
            size_t N1 = N/2; 
            bitonicSort(buffer, N1, !ascend);
            bitonicSort(buffer + (block_size * N1), N-N1, ascend);
            bitonicMerge(buffer, N, ascend);
        }
    }

    // 重写 sort 方法
    template<typename KeyType>
    void BitonicSorter<KeyType>::sort(std::vector<KeyType>& array) {
        // 对整个数组进行双调排序
        bitonicSort((unsigned char*)array.data(), array.size(), true);

    }

    template class obl::BitonicSorter<int>; 
    template class obl::BitonicSorter<double>; 
    template class obl::BitonicSorter<std::string>; 
}
