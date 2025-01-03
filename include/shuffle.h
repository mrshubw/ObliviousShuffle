#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <memory> 
#include "wakson/RecursiveShuffle/RecursiveShuffle.hpp"
#include "wakson/WaksmanNetwork/WaksmanNetwork.hpp"
#include "sorter.h"

namespace obl
{
    class OShuffler
    {
    public:
        enum class Method {BitonicShuffle, RecursiveShuffle, WaksmanShuffle};
        Method method = Method::BitonicShuffle;
        using TagType = uint32_t;

        OShuffler() {}
        OShuffler(Method method) : method(method) {}

        void shuffle(uint8_t *buf, size_t N, size_t block_size);
        // 逆shuffle,用于恢复原始顺序。BitonicShuffle和RecursiveShuffle的逆shuffle基于obliviousAssign函数，WaksmanShuffle的逆shuffle基于Waksman自带的inversePermutation函数。
        void inverseShuffle(uint8_t *buf, size_t block_size);
        void inverseShuffle(uint8_t *buf, size_t block_size, uint8_t *out_buf, size_t offset=0);

    private:
        std::vector<TagType> idx; // 用于记录每一项在输入buf中的位置,BitonicShuffle和RecursiveShuffle需要
        std::unique_ptr<WaksmanNetwork> wnet; // WaksmanShuffle需要的网络结构

        // 在数组的每一项前面添加一个tag，tag的类型为size_t。若tag随机选取，则根据tag排序能够实现shuffle输入buf
        size_t attachTags(uint8_t *buf, size_t N, size_t block_size, TagType *tags, uint8_t *tags_buf);
        /*
            去除attachTags函数中添加的tag，并将结果输出到buf中。
        */
        size_t detachTags(uint8_t *tags_buf, size_t N, size_t block_size, uint8_t *buf);
        size_t detachTags(uint8_t *tags_buf, size_t N, size_t block_size, uint8_t *buf, TagType *tags);
        void bitonicShuffle(uint8_t *buf, size_t N, size_t block_size);
        void recursiveShuffle(uint8_t *buf, size_t N, size_t block_size);
        void waksmanShuffle(uint8_t *buf, size_t N, size_t block_size);
    };
}