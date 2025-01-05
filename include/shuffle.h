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
    using TagType = uint32_t;

    // enum class Method {BitonicShuffle, RecursiveShuffle, WaksmanShuffle};
    class OShuffler
    {
    public:
        virtual ~OShuffler() = default; // 虚析构函数
        virtual void shuffle(uint8_t *buf, size_t N, size_t block_size) = 0;
        // 逆shuffle,用于恢复原始顺序。BitonicShuffle和RecursiveShuffle的逆shuffle基于obliviousAssign函数，WaksmanShuffle的逆shuffle基于Waksman自带的inversePermutation函数。
        virtual void inverseShuffle(uint8_t *buf, size_t block_size) = 0;
        virtual void inverseShuffle(uint8_t *buf, size_t block_size, uint8_t *out_buf, size_t offset=0) = 0;

        static std::unique_ptr<OShuffler> create(std::string method);

    protected:
        std::string method;
        // void bitonicShuffle(uint8_t *buf, size_t N, size_t block_size);
        // void recursiveShuffle(uint8_t *buf, size_t N, size_t block_size);
        // void waksmanShuffle(uint8_t *buf, size_t N, size_t block_size);
    };

    class OShufflerWithIndex : public OShuffler
    {
    public:
        void shuffle(uint8_t *buf, size_t N, size_t block_size);
        void inverseShuffle(uint8_t *buf, size_t block_size);
        void inverseShuffle(uint8_t *buf, size_t block_size, uint8_t *out_buf, size_t offset=0);

    private:
        std::vector<TagType> idx; // 用于记录每一项在输入buf中的位置,BitonicShuffle和RecursiveShuffle需要

        virtual void shuffleKernel(uint8_t *buf, size_t N, size_t block_size) = 0;
    };

    class BitonicShuffler : public OShufflerWithIndex
    {
    public:
        BitonicShuffler() {
            method = "BitonicShuffle";
        }
    private:
        void shuffleKernel(uint8_t *buf, size_t N, size_t block_size) override;
    };

    class RecursiveShuffler : public OShufflerWithIndex
    {
    public:
        RecursiveShuffler() {
            method = "RecursiveShuffle";
        }
    private:
        void shuffleKernel(uint8_t *buf, size_t N, size_t block_size) override;
    };

    class WaksmanShuffler : public OShuffler
    {
    public:
        WaksmanShuffler() {
            method = "WaksmanShuffle";
        }
        void shuffle(uint8_t *buf, size_t N, size_t block_size) override;
        void inverseShuffle(uint8_t *buf, size_t block_size) override;
        void inverseShuffle(uint8_t *buf, size_t block_size, uint8_t *out_buf, size_t offset=0) override;

    private:
        std::unique_ptr<WaksmanNetwork> wnet; // WaksmanShuffle需要的网络结构
    };
}