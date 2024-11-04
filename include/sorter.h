#pragma once
#include <vector>
#include <string>
#include <obl_primitives_ext.h>

namespace obl {

    template<typename KeyType>
    class OSorter {
    public:
        virtual ~OSorter() = default;
        virtual void sort(std::vector<KeyType>& array) = 0; // 纯虚函数，具体算法需实现
        
    protected:
        // 比较并交换
        inline void compare_and_swap(KeyType& a, KeyType& b, bool ascend){
            if ((a > b && ascend) || (a < b && !ascend)) {
            std::swap(a, b);
            }
        };
    };

    template<typename KeyType>
    class BitonicSorter : public OSorter<KeyType> {
    public:
        void sort(std::vector<KeyType>& array) override; // 重写基类的 sort 方法
        
    private:
        void bitonicMerge(unsigned char *buffer, size_t N, bool ascend); // 合并双调序列
        void bitonicSort(unsigned char *buffer, size_t N, bool ascend); // 递归排序
    };
}
