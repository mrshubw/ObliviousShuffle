#pragma once
#include <vector>
#include "sorter.h"

namespace obl {

    class BitonicSorter : public Sorter {
    public:
        void sort(std::vector<int>& array) override; // 重写基类的 sort 方法
        
    private:
        void compare_and_swap(int& a, int& b, bool dir); // 比较并交换
        void bitonic_merge(std::vector<int>& array, int low, int cnt, bool dir); // 合并双调序列
        void bitonic_sort(std::vector<int>& array, int low, int cnt, bool dir); // 递归排序
    };

}
