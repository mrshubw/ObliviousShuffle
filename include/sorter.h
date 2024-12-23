#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <obl_primitives_ext.h>
#include "wakson/SortingNetwork/SortingNetwork.hpp"

namespace obl {

    class OSorter {
    public:
        std::string method = "bitonic"; // 默认使用 bitonic 排序

        OSorter(std::string method = "bitonic") : method(method) {};
        ~OSorter() = default;

        template<typename KeyType>
        void sort(std::vector<KeyType>& array){
            bitonicSort(array);
        };

        // wakson库提供的BitonicSort接口有误，没有正确地传入KeyType，这里重新实现一个接口
        template<typename KeyType>
        void bitonicSort(std::vector<KeyType>& array){
            unsigned char* buffer = reinterpret_cast<unsigned char*>(array.data());
            size_t N = array.size();
            size_t block_size = sizeof(KeyType);
            bool ascend = true;
            if(block_size==4){
                BitonicSort<OSWAP_4, KeyType>(buffer, N, block_size, ascend);
            } else if(block_size==8){
                BitonicSort<OSWAP_8, KeyType>(buffer, N, block_size, ascend);
            } else if(block_size==12){
                BitonicSort<OSWAP_12, KeyType>(buffer, N, block_size, ascend);
            } else if (block_size%16==0){
                BitonicSort<OSWAP_16X, KeyType>(buffer, N, block_size, ascend);
            }
            else{
                BitonicSort<OSWAP_8_16X, KeyType>(buffer, N, block_size, ascend);
            }
        };
    };
}
