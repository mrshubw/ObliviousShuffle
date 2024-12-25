#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "shuffle.h" // 包含你的OShuffler类定义

// 测试类定义
class OShufflerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 初始化一个简单的缓冲区，用于测试
        data = std::vector<uint32_t>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
        N = data.size();
        block_size = 4;
        buf = reinterpret_cast<unsigned char*>(data.data());
    }

    void TearDown() override {
        // 清理工作，如果有的话
    }

    unsigned char *buf;
    uint64_t N;
    size_t block_size;
    std::vector<uint32_t> data;
};

// 测试用例：检查shuffle之后元素数量和内容是否正确
TEST_F(OShufflerTest, ShufflePreservesElements) {
    obl::OShuffler shuffler;
    std::vector<uint32_t> original_data(data);

    shuffler.shuffle(buf, N, block_size);

    print_array(data, N);
    print_array(original_data, N);

    // 对原始数据进行排序
    std::sort(original_data.begin(), original_data.end());
    // 对shuffle之后的数据进行排序
    std::sort(data.begin(), data.end());

    // 检查排序后的原始数据和shuffle之后的数据是否相同
    EXPECT_EQ(original_data, data);
}


// todo: 先使用uint32_t测试一下shuffle的整体正确性，在扩展oswap_buffer函数能够处理的类型，最后简化shuffle函数的实现