#include <vector>
#include <algorithm>
#include <random>
#include <gtest/gtest.h>
#include "sorter.h"

// 全局的测试函数
void test_bitonic_sort(const std::vector<int>& input, const std::vector<int>& expected) {
    obl::BitonicSorter bitonic_sort;
    std::vector<int> copy = input; // 创建输入的副本
    bitonic_sort.sort(copy);
    ASSERT_EQ(copy, expected); // 验证排序结果
}

class BitonicSortTestHelper {
public:
    // 生成测试数据的函数
    static std::vector<int> generate_test_data(int case_type, int size) {
        std::vector<int> data(size);
        switch (case_type) {
            case 0: // 随机数组
                fill_random_array(data);
                break;
            case 1: // 逆序数组
                fill_descending_array(data);
                break;
            case 2: // 正序数组
                fill_ascending_array(data);
                break;
            case 3: // 包含重复元素的数组
                fill_array_with_duplicates(data);
                break;
            case 4: // 包含负数的数组
                fill_array_with_negatives(data);
                break;
            case 5: // 空数组
                data.clear();
                break;
            case 6: // 单元素数组
                data = {1};
                break;
            default:
                throw std::invalid_argument("Invalid case type");
        }
        return data;
    }

    // 验证排序结果
    static void verify_sort(const std::vector<int>& data) {
        std::vector<int> sorted_data = data;
        std::sort(sorted_data.begin(), sorted_data.end());
        test_bitonic_sort(data, sorted_data);
    }

private:
    static void fill_random_array(std::vector<int>& data) {
        std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<int> dist(1, 1000);
        std::generate(data.begin(), data.end(), [&]() { return dist(gen); });
    }

    static void fill_descending_array(std::vector<int>& data) {
        std::iota(data.begin(), data.end(), 1);
        std::reverse(data.begin(), data.end());
    }

    static void fill_ascending_array(std::vector<int>& data) {
        std::iota(data.begin(), data.end(), 1);
    }

    static void fill_array_with_duplicates(std::vector<int>& data) {
        std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<int> dist(1, data.size() / 10);
        for (int i = 0; i < data.size(); ++i) {
            data[i] = dist(gen);
        }
    }

    static void fill_array_with_negatives(std::vector<int>& data) {
        std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<int> dist(-500, 500);
        std::generate(data.begin(), data.end(), [&]() { return dist(gen); });
    }
};

// 参数化测试
TEST(BitonicSortTests, TestVariousArrayTypes) {
    const std::vector<int> sizes = {0, 1, 5, 10, 20, 100};
    for (int size : sizes) {
        for (int case_type = 0; case_type <= 6; ++case_type) {
            auto data = BitonicSortTestHelper::generate_test_data(case_type, size);
            BitonicSortTestHelper::verify_sort(data);
        }
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
