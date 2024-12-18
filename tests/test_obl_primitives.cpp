#include <gtest/gtest.h>
#include "obl_primitives_ext.h"  // 包含包含 oswap 函数的头文件

// 测试 oswap 函数
TEST(OSwapTest, SwapBlocks) {
    const size_t block_size = 4;  // 定义块大小
    uint8_t block1[block_size] = {1, 2, 3, 4};
    uint8_t block2[block_size] = {5, 6, 7, 8};

    // 调用 oswap 函数进行交换
    oswap(block1, block2, block_size, true);

    // 验证数据是否交换
    EXPECT_EQ(block1[0], 5);
    EXPECT_EQ(block1[1], 6);
    EXPECT_EQ(block1[2], 7);
    EXPECT_EQ(block1[3], 8);
    EXPECT_EQ(block2[0], 1);
    EXPECT_EQ(block2[1], 2);
    EXPECT_EQ(block2[2], 3);
    EXPECT_EQ(block2[3], 4);
}

TEST(OSwapTest, NoSwap) {
    const size_t block_size = 4;  // 定义块大小
    uint8_t block1[block_size] = {1, 2, 3, 4};
    uint8_t block2[block_size] = {5, 6, 7, 8};

    // 不进行交换
    oswap(block1, block2, block_size, false);

    // 验证数据未改变
    EXPECT_EQ(block1[0], 1);
    EXPECT_EQ(block1[1], 2);
    EXPECT_EQ(block1[2], 3);
    EXPECT_EQ(block1[3], 4);
    EXPECT_EQ(block2[0], 5);
    EXPECT_EQ(block2[1], 6);
    EXPECT_EQ(block2[2], 7);
    EXPECT_EQ(block2[3], 8);
}

// 模板测试函数
template <typename T>
void test_oswap() {
    const size_t block_size = 4;  // 定义块大小
    T block1[block_size] = {1, 2, 3, 4};
    T block2[block_size] = {5, 6, 7, 8};

    // 调用 oswap 函数进行交换
    oswap(reinterpret_cast<uint8_t*>(block1), reinterpret_cast<uint8_t*>(block2), block_size * sizeof(T), true);

    // 验证数据是否交换
    for (size_t i = 0; i < block_size; ++i) {
        EXPECT_EQ(block1[i], static_cast<T>(5 + i));  // 5, 6, 7, 8
        EXPECT_EQ(block2[i], static_cast<T>(1 + i));  // 1, 2, 3, 4
    }
}

TEST(OSwapTest, SwapUInt8) {
    test_oswap<uint8_t>();
}

TEST(OSwapTest, SwapUInt16) {
    test_oswap<uint16_t>();
}

TEST(OSwapTest, SwapUInt32) {
    test_oswap<uint32_t>();
}

TEST(OSwapTest, SwapFloat) {
    test_oswap<float>();
}

TEST(OSwapTest, SwapDouble) {
    test_oswap<double>();
}

// string is not supported by oswap function temporarily
// 测试 oswap 函数对 std::string 类型的交换能力
// TEST(OSwapTest, SwapString) {
//     std::string str1 = "Hello";
//     std::string str2 = "World";

//     // 提取 std::string 的地址并进行交换
//     oswap(reinterpret_cast<uint8_t*>(&str1), reinterpret_cast<uint8_t*>(&str2), sizeof(std::string), true);

//     // 结果可能各自持有原来的数据，导致未定义行为
//     std::cout << str1 << std::endl; // 未定义行为
//     std::cout << str2 << std::endl; // 未定义行为


//     // 由于 std::string 结构体内部有不同成员，确保交换后的内容正确
//     EXPECT_EQ(str1, "World");  // 期待 str1 变为 "World"
//     EXPECT_EQ(str2, "Hello");  // 期待 str2 变为 "Hello"
// }
