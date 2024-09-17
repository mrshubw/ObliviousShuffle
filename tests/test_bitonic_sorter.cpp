#include <cassert>
#include <vector>
#include <iostream>
#include "sorter.h"

void test_bitonic_sort() {
    obl::BitonicSorter bitonic_sort;

    // 测试用例 1：4个元素的数组
    std::vector<int> array1 = {4, 1, 3, 2};
    bitonic_sort.sort(array1);
    assert((array1 == std::vector<int>{1, 2, 3, 4}));

    // 测试用例 2：8个元素的数组
    std::vector<int> array2 = {8, 5, 6, 2, 3, 4, 1, 7};
    bitonic_sort.sort(array2);
    assert((array2 == std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8}));

    // 测试用例 3：2个元素的数组
    std::vector<int> array3 = {3, 1};
    bitonic_sort.sort(array3);
    assert((array3 == std::vector<int>{1, 3}));

    // 测试用例 4：8个元素的已排序数组
    std::vector<int> array4 = {1, 2, 3, 4, 5, 6, 7, 8};
    bitonic_sort.sort(array4);
    assert((array4 == std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8}));

    // 测试用例 5：8个元素的重复元素数组
    std::vector<int> array5 = {3, 1, 2, 1, 3, 4, 4, 2};
    bitonic_sort.sort(array5);
    assert((array5 == std::vector<int>{1, 1, 2, 2, 3, 3, 4, 4}));

    // 测试用例 6：8个元素的相同元素数组
    std::vector<int> array6 = {5, 5, 5, 5, 5, 5, 5, 5};
    bitonic_sort.sort(array6);
    assert((array6 == std::vector<int>{5, 5, 5, 5, 5, 5, 5, 5}));

    std::cout << "All Bitonic Sort tests passed!" << std::endl;
}

int main() {
    test_bitonic_sort();
    return 0;
}
