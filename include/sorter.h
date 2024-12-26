#pragma once
#include <vector>
#include <string>
#include <iostream>
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
            BitonicSort(array.data(),  array.size(), true);
        };

        //TODO：oswap交换的类型和ogt比较的类型可以不一致，这种特质使得我们可以为每项添加tag实现shuffle
    };
}
