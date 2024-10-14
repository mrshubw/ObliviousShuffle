#include "sorter.h"
#include <cmath> // 添加头文件以使用 log2 和 pow

namespace obl {

    // 比较并交换两个元素
    void BitonicSorter::compare_and_swap(int& a, int& b, bool dir) {
        if ((a > b && dir) || (a < b && !dir)) {
            std::swap(a, b);
        }
    }

    // 递归进行双调排序
    void BitonicSorter::bitonic_merge(std::vector<int>& array, int low, int cnt, bool dir) {
        if (cnt > 1) {
            int k = cnt / 2;
            for (int i = low; i < low + k; i++) {
                compare_and_swap(array[i], array[i + k], dir);
            }
            bitonic_merge(array, low, k, dir);
            bitonic_merge(array, low + k, k, dir);
        }
    }

    // 双调排序算法
    void BitonicSorter::bitonic_sort(std::vector<int>& array, int low, int cnt, bool dir) {
        if (cnt > 1) {
            int k = cnt / 2;
            // 先对前一半排序，升序
            bitonic_sort(array, low, k, true);
            // 后一半排序，降序
            bitonic_sort(array, low + k, k, false);
            // 合并两个部分
            bitonic_merge(array, low, cnt, dir);
        }
    }

    // 重写 sort 方法
    void BitonicSorter::sort(std::vector<int>& array) {
        int n = array.size();
        // 计算填充到下一个2的幂次的长度
        int next_power_of_2 = pow(2, std::ceil(log2(n)));
        array.resize(next_power_of_2); // 调整数组大小

        // 使用最大值填充新增加的部分
        std::fill(array.begin() + n, array.end(), std::numeric_limits<int>::max());

        // 对整个数组进行双调排序
        bitonic_sort(array, 0, array.size(), true);

        // 裁剪数组，去掉填充的元素
        array.resize(n);
    }

}
