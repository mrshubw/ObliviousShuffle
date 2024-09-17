#pragma once
#include <vector>

namespace obl {

    class Sorter {
    public:
        virtual ~Sorter() = default;
        virtual void sort(std::vector<int>& array) = 0; // 纯虚函数，具体算法需实现
    };

    class BitonicSorter : public Sorter {
    public:
        void sort(std::vector<int>& array) override; // 重写基类的 sort 方法
        
    private:
        void compare_and_swap(int& a, int& b, bool dir); // 比较并交换
        void bitonic_merge(std::vector<int>& array, int low, int cnt, bool dir); // 合并双调序列
        void bitonic_sort(std::vector<int>& array, int low, int cnt, bool dir); // 递归排序
    };
}
