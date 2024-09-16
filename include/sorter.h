#pragma once
#include <vector>

namespace obl {

    class Sorter {
    public:
        virtual ~Sorter() = default;
        virtual void sort(std::vector<int>& array) = 0; // 纯虚函数，具体算法需实现
    };

}
