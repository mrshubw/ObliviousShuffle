#include <vector>
#include <algorithm>
#include <random>
#include <gtest/gtest.h>
#include "sorter.h"

template <typename T>
std::vector<T> generateRandomArray(int size) {
    std::vector<T> data(size);
    std::mt19937 gen(std::random_device{}()); // 使用随机数引擎

    if constexpr (std::is_same_v<T, int>) {
        std::uniform_int_distribution<int> dist(1, 1000); // 整数范围
        std::generate(data.begin(), data.end(), [&]() { return dist(gen); });
    } 
    else if constexpr (std::is_same_v<T, double>) {
        std::uniform_real_distribution<double> dist(1.0, 1000.0); // 浮点数范围
        std::generate(data.begin(), data.end(), [&]() { return dist(gen); });
    } 
    else if constexpr (std::is_same_v<T, std::string>) {
        std::vector<std::string> options = {"apple", "orange", "banana", "grape", "peach"};
        std::uniform_int_distribution<int> dist(0, options.size() - 1);
        std::generate(data.begin(), data.end(), [&]() { return options[dist(gen)]; });
    }

    return data;
}

template <typename Sorter>
class SortTestHelper: public testing::Test {
protected:
    static void SetUpTestCase() {
        // 任何全局的初始化代码
    }

    static void TearDownTestCase() {
        // 任何全局的清理代码
    }

    void SetUp() {
        // 任何共享的初始化代码
    }

    void TearDown() {
        // 任何共享的清理代码
    }

    // 给定输入和预期输出，验证排序算法的正确性
    template <typename T>
    void verify_sort(const std::vector<T>& input, const std::vector<T>& expected) {
        Sorter sorter;
        std::vector<T> copy = input;
        sorter.sort(copy);
        ASSERT_EQ(copy, expected);
    }

    // 在随机数组上测试一次排序算法
    template <typename T>
    void testRandomArray(int size) {
        // 生成测试数据
        std::vector<T> input = generateRandomArray<T>(size);
        std::vector<T> expected = input;
        std::sort(expected.begin(), expected.end());

        // 验证排序结果
        verify_sort(input, expected);
    }
};

// 在可能的输入大小和输入类型上测试排序算法
using BitonicSortIntTest = SortTestHelper<obl::BitonicSorter<int>>;
TEST_F(BitonicSortIntTest, TestRandomArray) {
    std::vector<int> test_size = {8, 128, 1024, 10, 100, 1000};
    for (int size : test_size) {
        testRandomArray<int>(size);
    }
}

using BitonicSortDoubleTest = SortTestHelper<obl::BitonicSorter<double>>;
TEST_F(BitonicSortDoubleTest, TestRandomArray) {
    std::vector<int> test_size = {8, 128, 1024, 10, 100, 1000};
    for (int size : test_size) {
        testRandomArray<double>(size);
    }
}

using BitonicSortStringTest = SortTestHelper<obl::BitonicSorter<std::string>>;
TEST_F(BitonicSortStringTest, TestRandomArray) {
    std::vector<int> test_size = {8, 128, 1024, 10, 100, 1000};
    for (int size : test_size) {
        testRandomArray<std::string>(size);
    }
}