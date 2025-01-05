#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "shuffle.h" // 包含你的OShuffler类定义

// 模板测试类定义
template <typename T>
class OShufflerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 初始化一个简单的缓冲区，用于测试
        data = std::vector<T>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}; // 初始化为模板类型
        N = data.size();
        block_size = sizeof(T); // 设置block_size为每个元素的大小
        buf = reinterpret_cast<unsigned char*>(data.data());
    }

    void TearDown() override {
        // 清理工作，如果有的话
    }

    void verifyShuffle(std::string method) {
        auto shuffler = obl::OShuffler::create(method);
        std::vector<T> original_data(data);

        shuffler->shuffle(buf, N, block_size);

        print_array(data, N);           // 确保print_array能够处理T类型
        print_array(original_data, N);  // 确保print_array能够处理T类型

        // 对原始数据进行排序
        std::sort(original_data.begin(), original_data.end());
        // 对shuffle之后的数据进行排序
        std::sort(data.begin(), data.end());

        // 检查排序后的原始数据和shuffle之后的数据是否相同
        EXPECT_EQ(original_data, data);
    }

    void verifyInverseShuffle(std::string method) {
        auto shuffler = obl::OShuffler::create(method);
        std::vector<T> original_data(data);

        // 先进行Shuffle操作
        shuffler->shuffle(buf, N, block_size);

        // 保存Shuffle后的数据
        std::vector<T> shuffled_data(data);

        // 调用inverseShuffle恢复数据顺序
        shuffler->inverseShuffle(buf, block_size);

        // 打印恢复后的数据
        print_array(data, N);

        // 检查恢复后的数据是否与原始数据相同
        EXPECT_EQ(original_data, data);
    }

    unsigned char *buf;
    uint64_t N;
    size_t block_size;
    std::vector<T> data;
};

// TODO: 先使用uint32_t测试一下shuffle的整体正确性，在扩展oswap_buffer函数能够处理的类型后，使用多种不同长度的数据类型进行测试
// 针对不同数据类型的测试实例化
using ShufflerTypes = ::testing::Types<uint32_t, float, double, int64_t, uint64_t>;

TYPED_TEST_SUITE(OShufflerTest, ShufflerTypes);

// 测试用例：检查Bitonic Shuffle是否保持元素
TYPED_TEST(OShufflerTest, BitonicShufflePreservesElements) {
    this->verifyShuffle("BitonicShuffler");
}

// 测试用例：检查Recursive Shuffle是否保持元素
TYPED_TEST(OShufflerTest, RecursiveShufflePreservesElements) {
    this->verifyShuffle("RecursiveShuffler");
}

// 测试用例：检查Waksman Shuffle是否保持元素
TYPED_TEST(OShufflerTest, WaksmanShufflePreservesElements) {
    this->verifyShuffle("WaksmanShuffler");
}

// 测试用例：检查Bitonic Shuffle的inverseShuffle是否能够正确恢复数据顺序
TYPED_TEST(OShufflerTest, BitonicInverseShuffleRestoresOrder) {
    this->verifyInverseShuffle("BitonicShuffler");
}

// 测试用例：检查Recursive Shuffle的inverseShuffle是否能够正确恢复数据顺序
TYPED_TEST(OShufflerTest, RecursiveInverseShuffleRestoresOrder) {
    this->verifyInverseShuffle("RecursiveShuffler");
}

// 测试用例：检查Waksman Shuffle的inverseShuffle是否能够正确恢复数据顺序
TYPED_TEST(OShufflerTest, WaksmanInverseShuffleRestoresOrder) {
    this->verifyInverseShuffle("WaksmanShuffler");
}
