#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "wakson/RecursiveShuffle/RecursiveShuffle.hpp"
#include "sorter.h"

namespace obl
{
    class OShuffler
    {
    public:
        enum class Method {BitonicShuffle, RecursiveShuffle};
        Method method = Method::BitonicShuffle;

        OShuffler() {}
        OShuffler(Method method) : method(method) {}

        void shuffle(uint8_t *buf, size_t N, size_t block_size);

    private:
        // 在数组的每一项前面添加一个tag，tag的类型为size_t。若tag随机选取，则根据tag排序能够实现shuffle输入buf
        size_t attachTags(uint8_t *buf, size_t N, size_t block_size, size_t *tags, uint8_t *tags_buf);
        /*
            去除attachTags函数中添加的tag，并将结果输出到buf中。
        */
        size_t detachTags(uint8_t *tags_buf, size_t N, size_t block_size, uint8_t *buf);
        void bitonicShuffle(uint8_t *buf, size_t N, size_t block_size);
        void recursiveShuffle(uint8_t *buf, size_t N, size_t block_size);
    };
}