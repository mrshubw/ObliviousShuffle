#include <cassert>
#include <vector>
#include <iostream>
#include "sorter.h"

// 辅助函数，用于排序并验证结果
void test_sort(const std::vector<int>& input, const std::vector<int>& expected) {
    obl::BitonicSorter bitonic_sort;
    std::vector<int> copy = input; // 创建输入的副本
    bitonic_sort.sort(copy);
    assert(copy == expected); // 验证排序结果
}

void test_bitonic_sort() {
    // 测试用例
    test_sort({4, 1, 3, 2}, {1, 2, 3, 4}); // 4个元素的数组
    test_sort({8, 5, 6, 2, 3, 4, 1, 7}, {1, 2, 3, 4, 5, 6, 7, 8}); // 8个元素的数组
    test_sort({3, 1}, {1, 3}); // 2个元素的数组
    test_sort({1, 2, 3, 4, 5, 6, 7, 8}, {1, 2, 3, 4, 5, 6, 7, 8}); // 已排序数组
    test_sort({3, 1, 2, 1, 3, 4, 4, 2}, {1, 1, 2, 2, 3, 3, 4, 4}); // 重复元素数组
    test_sort({5, 5, 5, 5, 5, 5, 5, 5}, {5, 5, 5, 5, 5, 5, 5, 5}); // 相同元素数组

    std::cout << "All Bitonic Sort tests passed!" << std::endl;
}

int main() {
    test_bitonic_sort();
    return 0;
}
