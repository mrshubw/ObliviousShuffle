#include "shuffle.h"
#include "wakson/WaksmanNetwork/WaksmanNetwork.hpp"
#include "obl_primitives.h"

namespace obl
{
    size_t OShuffler::attachTags(uint8_t *buf, size_t N, size_t block_size, TagType *tags, uint8_t *tags_buf)
    {
        size_t tag_size = sizeof(TagType);
        size_t block_size_with_tag = block_size + tag_size;

        // 如果 tags_buf 尚未分配内存，则分配所需的内存以容纳添加tag后的block
        if (buf == NULL)
        {
            buf = reinterpret_cast<uint8_t *>(malloc(N * block_size_with_tag));
            if (buf == NULL)
            {
                printf("Malloc failed in attacheTag\n");
                return -1; // 添加返回值以处理内存分配失败的情况
            }
        }

        uint8_t *tags_buf_ptr = tags_buf;
        uint8_t *buf_ptr = buf;
        uint8_t *tags_ptr = reinterpret_cast<uint8_t *>(tags);

        for (size_t i = 0; i < N; i++)
        {
            // 复制随机tag到tags_buf
            memcpy(tags_buf_ptr, tags_ptr, tag_size);
            tags_ptr += tag_size;
            tags_buf_ptr += tag_size; 

            // 复制block到tags_buf后面
            memcpy(tags_buf_ptr, buf_ptr, block_size);
            buf_ptr += block_size;
            tags_buf_ptr += block_size;
        }

        return block_size_with_tag;
    }

    size_t OShuffler::detachTags(uint8_t *tags_buf, size_t N, size_t block_size, uint8_t *buf){
        size_t tag_size = sizeof(TagType);
        size_t real_block_size = block_size - tag_size;

        uint8_t *tags_buf_ptr = tags_buf;
        uint8_t *buf_ptr = buf;

        for (size_t i = 0; i < N; i++)
        {
            // 跳过随机tag
            tags_buf_ptr += tag_size;

            // 复制block到buf
            memcpy(buf_ptr, tags_buf_ptr, real_block_size);
            buf_ptr += real_block_size;
            tags_buf_ptr += real_block_size;
        }

        return real_block_size;
    }

    size_t OShuffler::detachTags(uint8_t *tags_buf, size_t N, size_t block_size, uint8_t *buf, TagType *tags){
        size_t tag_size = sizeof(TagType);
        size_t real_block_size = block_size - tag_size;

        uint8_t *tags_buf_ptr = tags_buf;
        uint8_t *buf_ptr = buf;
        TagType *tags_ptr = tags;

        for (size_t i = 0; i < N; i++)
        {
            // 取出tag
            memcpy(tags_ptr, tags_buf_ptr, tag_size);
            tags_ptr += 1;
            tags_buf_ptr += tag_size;

            // 复制block到buf
            memcpy(buf_ptr, tags_buf_ptr, real_block_size);
            buf_ptr += real_block_size;
            tags_buf_ptr += real_block_size;
        }

        return real_block_size;
    }

    void OShuffler::bitonicShuffle(uint8_t *buf, size_t N, size_t block_size){
        // 添加随机tag
        TagType *tags = new TagType[N];
        PRB_buffer::getInstance().getBulkRandomBytes(reinterpret_cast<uint8_t *>(tags), N * sizeof(TagType));
        uint8_t *tags_buf = new uint8_t[N * (block_size + sizeof(TagType))];
        block_size = attachTags(buf, N, block_size, tags, tags_buf);

        // 以tag为key，block为单位，进行bitonic排序
        BitonicSort<TagType>(tags_buf, N, block_size, true);

        // 移除tag
        block_size = detachTags(tags_buf, N, block_size, buf);

        delete[] tags;
        delete[] tags_buf;
    }

    void OShuffler::recursiveShuffle(uint8_t *buf, size_t N, size_t block_size){
        RecursiveShuffle_M1(buf, N, block_size);
    }

    void OShuffler::waksmanShuffle(uint8_t *buf, size_t N, size_t block_size){
        uint32_t *random_permutation;
        try {
            random_permutation = new uint32_t[N];
        } catch (std::bad_alloc&) {
            printf("Allocating memory failed in OblivWaksmanShuffle\n");
        }
        // Generate random permutation
        generateRandomPermutation(N, random_permutation);

        // Set control bits to implement randomly generated permutation
        wnet = std::make_unique<WaksmanNetwork>(((uint32_t) N));
        //printf("\nSetting control bits\n");
        wnet->setPermutation(random_permutation);

        // Apply the permutation
        //printf("\n Applying permutation\n");
        if (block_size == 4) {
            wnet->applyPermutation<OSWAP_4>(buf, block_size);
        } else if (block_size == 8) {
            wnet->applyPermutation<OSWAP_8>(buf, block_size);
        } else if (block_size == 12) {
            wnet->applyPermutation<OSWAP_12>(buf, block_size);
        } else if (block_size%16 == 0) {
            wnet->applyPermutation<OSWAP_16X>(buf, block_size);
        } else {
            wnet->applyPermutation<OSWAP_8_16X>(buf, block_size);
        }

        delete[] random_permutation;
    }

    void OShuffler::shuffle(uint8_t *buf, size_t N, size_t block_size)
    {
        uint8_t *buffer = buf;
        // 当shuffle方法为bitonic shuffle或recursive shuffle时，需要添加索引idx表示每个block的原始位置
        if (method == Method::BitonicShuffle || method == Method::RecursiveShuffle)
        {
            // 初始化添加了idx的buf
            size_t block_size_with_idx = block_size + sizeof(TagType);
            uint8_t *idx_buf = new uint8_t[N * block_size_with_idx];

            // 初始化idx
            idx.resize(N);
            for (size_t i = 0; i < N; i++)
            {
                idx[i] = i;
            }

            // 添加idx到buf
            attachTags(buf, N, block_size, idx.data(), idx_buf);

            // 使用添加了idx的buf替代原buf进行shuffle
            buffer = idx_buf;
            block_size = block_size_with_idx;
        }

        switch (method)
        {
        case Method::BitonicShuffle:
            bitonicShuffle(buffer, N, block_size);
            break;

        case Method::RecursiveShuffle:
            recursiveShuffle(buffer, N, block_size);
            break;

        case Method::WaksmanShuffle:
            waksmanShuffle(buffer, N, block_size);
            break;
        
        default:
            std::cerr << "Invalid method" << std::endl;
            break;
        }

        // 当shuffle方法为bitonic shuffle或recursive shuffle时，需要移除idx
        if (method == Method::BitonicShuffle || method == Method::RecursiveShuffle)
        {
            // 移除idx
            block_size = detachTags(buffer, N, block_size, buf, idx.data());

            // 释放idx_buf
            delete[] buffer;
        }
    };

    void OShuffler::inverseShuffle(uint8_t *buf, size_t block_size){
        if (method == Method::BitonicShuffle || method == Method::RecursiveShuffle)
        {
            // 需要空间临时存放结果，否则shuffle结果会覆盖原buf
            uint8_t *temp_buf = new uint8_t[idx.size() * block_size];

            // 根据idx将shuffle结果恢复顺序
            for (size_t i = 0; i < idx.size(); i++)
            {
                ObliviousArrayAssignBytes(temp_buf, buf + i * block_size, block_size, idx[i], idx.size());
            }

            // 将temp_buf中的内容复制到输出buf中
            memcpy(buf, temp_buf, idx.size() * block_size);
            
        } else if (method == Method::WaksmanShuffle) {
            // 调用WaksmanNetwork的inversePermutation函数
            if (block_size == 4) {
                wnet->applyInversePermutation<OSWAP_4>(buf, block_size);
            } else if (block_size == 8) {
                wnet->applyInversePermutation<OSWAP_8>(buf, block_size);
            } else if (block_size == 12) {
                wnet->applyInversePermutation<OSWAP_12>(buf, block_size);
            } else if (block_size%16 == 0) {
                wnet->applyInversePermutation<OSWAP_16X>(buf, block_size);
            } else {
                wnet->applyInversePermutation<OSWAP_8_16X>(buf, block_size);
            }
        }
        
    }

}