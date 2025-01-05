#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "shuffle.h"

// 模板测试类定义
template <typename T>
class OShufflerTest : public ::testing::Test {
protected:
    void SetUp() override {
        data = std::vector<T>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}; 
        N = data.size();
        block_size = sizeof(T);
        buf = reinterpret_cast<unsigned char*>(data.data());
    }

    void verifyShuffle(const std::string& method) {
        auto shuffler = obl::OShuffler::create(method);
        ASSERT_NE(shuffler, nullptr); // 确保 shuffler 创建成功

        std::vector<T> original_data(data);
        shuffler->shuffle(buf, N, block_size);

        std::sort(original_data.begin(), original_data.end());
        std::sort(data.begin(), data.end());

        EXPECT_EQ(original_data, data);
    }

    void verifyInverseShuffle(const std::string& method) {
        auto shuffler = obl::OShuffler::create(method);
        ASSERT_NE(shuffler, nullptr); // 确保 shuffler 创建成功

        std::vector<T> original_data(data);
        shuffler->shuffle(buf, N, block_size);
        shuffler->inverseShuffle(buf, block_size);

        EXPECT_EQ(original_data, data);
    }

    unsigned char *buf;
    uint64_t N;
    size_t block_size;
    std::vector<T> data;
};

// 测试用例
using ShufflerTypes = ::testing::Types<uint32_t, float, double, int64_t, uint64_t>;

// 函数模板，用于获取 unordered_map 的 key 列表
template<typename K, typename V>
std::vector<K> getKeys(const std::unordered_map<K, V>& map) {
    std::vector<K> keys;
    for (const auto& pair : map) {
        keys.push_back(pair.first); // 添加每个 key 到 keys 向量中
    }
    return keys;
}

// 定义测试类
template <typename T>
class ShuffleTester : public OShufflerTest<T> {
public:
    static std::vector<std::string> getShuffleMethods() {
        return getKeys(obl::getOShufflerCreatorMap());
    }
};

// 参数化测试
TYPED_TEST_SUITE(ShuffleTester, ShufflerTypes);

// 单一测试用例，循环获取需要测试的 shuffler 类型
TYPED_TEST(ShuffleTester, PreserveElements) {
    for (const auto& method : ShuffleTester<TypeParam>::getShuffleMethods()) {
        this->verifyShuffle(method);
    }
}

TYPED_TEST(ShuffleTester, InverseShuffleRestoresOrder) {
    for (const auto& method : ShuffleTester<TypeParam>::getShuffleMethods()) {
        this->verifyInverseShuffle(method);
    }
}
