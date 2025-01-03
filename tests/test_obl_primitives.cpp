#include <gtest/gtest.h>
#include "wakson/oasm_lib.h"  // 包含 oswap_buffer 的声明

// 测试 oswap_buffer<OSWAP_ANY> 的基本帧
TEST(OswapBufferTest, BasicSwap) {
    // 测试基础数据
    unsigned char source[] = {1, 2, 3, 4, 5, 6, 7, 8};
    unsigned char dest[] = {9, 10, 11, 12, 13, 14, 15, 16};
    size_t buffersize = sizeof(source);

    // 调用 oswap_buffer 函数
    oswap_buffer<OSWAP_ANY>(dest, source, buffersize, 1);

    // 验证交换结果
    for (size_t i = 0; i < buffersize; ++i) {
        EXPECT_EQ(dest[i], i + 1);  // dest 应该具有 source 的内容
        EXPECT_EQ(source[i], i + 9); // source 应该具有原来的 dest 内容
    }
}

// 测试不同长度的内存交换
TEST(OswapBufferTest, VariableLengthSwap) {
    unsigned char source[24] = {1, 2, 3, 4, 5, 6, 7, 8,
                                  9, 10, 11, 12, 13, 14, 15, 16,
                                  17, 18, 19, 20, 21, 22, 23, 24};
    unsigned char dest[24] = {25, 26, 27, 28, 29, 30, 31, 32,
                               33, 34, 35, 36, 37, 38, 39, 40,
                               41, 42, 43, 44, 45, 46, 47, 48};
    
    size_t buffersize = sizeof(source);

    oswap_buffer<OSWAP_ANY>(dest, source, buffersize, 1);

    // 验证交换结果
    for (size_t i = 0; i < buffersize; ++i) {
        EXPECT_EQ(dest[i], i + 1);
        EXPECT_EQ(source[i], i + 25);
    }
}

// 测试零字节交换
TEST(OswapBufferTest, ZeroLengthSwap) {
    unsigned char source[] = {1};
    unsigned char dest[] = {2};
    size_t buffersize = 0; // 不交换任何字节

    oswap_buffer<OSWAP_ANY>(dest, source, buffersize, 1);

    // 确保源和目标未改变
    EXPECT_EQ(source[0], 1);
    EXPECT_EQ(dest[0], 2);
}