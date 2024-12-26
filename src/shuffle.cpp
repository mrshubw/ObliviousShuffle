#include "shuffle.h"

namespace obl
{
    size_t OShuffler::attachTags(uint8_t *buf, size_t N, size_t block_size, size_t *tags, uint8_t *tags_buf)
    {
        size_t tag_size = sizeof(size_t);
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
        size_t tag_size = sizeof(size_t);
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

    void OShuffler::bitonicShuffle(uint8_t *buf, size_t N, size_t block_size){
        // 添加随机tag
        size_t *tags = new size_t[N];
        PRB_buffer::getInstance().getBulkRandomBytes(reinterpret_cast<uint8_t *>(tags), N * sizeof(size_t));
        uint8_t *tags_buf = new uint8_t[N * (block_size + sizeof(size_t))];
        block_size = attachTags(buf, N, block_size, tags, tags_buf);

        // 以tag为key，block为单位，进行bitonic排序
        using KeyType = size_t;
        bool ascend = true;
        if(block_size==4){
            BitonicSort<OSWAP_4, KeyType>(tags_buf, N, block_size, ascend);
        } else if(block_size==8){
            BitonicSort<OSWAP_8, KeyType>(tags_buf, N, block_size, ascend);
        } else if(block_size==12){
            BitonicSort<OSWAP_12, KeyType>(tags_buf, N, block_size, ascend);
        } else if (block_size%16==0){
            BitonicSort<OSWAP_16X, KeyType>(tags_buf, N, block_size, ascend);
        }
        else{
            BitonicSort<OSWAP_8_16X, KeyType>(tags_buf, N, block_size, ascend);
        }

        // 移除tag
        block_size = detachTags(tags_buf, N, block_size, buf);

        delete[] tags;
        delete[] tags_buf;
    }

    void OShuffler::recursiveShuffle(uint8_t *buf, size_t N, size_t block_size){
        RecursiveShuffle_M1(buf, N, block_size);
    }

    void OShuffler::shuffle(uint8_t *buf, size_t N, size_t block_size)
    {
        switch (method)
        {
        case Method::BitonicShuffle:
            bitonicShuffle(buf, N, block_size);
            break;

        case Method::RecursiveShuffle:
            recursiveShuffle(buf, N, block_size);
            break;
        
        default:
            std::cerr << "Invalid method" << std::endl;
            break;
        }
    };

}