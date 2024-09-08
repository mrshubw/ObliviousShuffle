#include <cassert>
#include <vector>
#include <iostream>
#include "bitonic_sort.h"

void test_oblivious_shuffle() {
    std::vector<int> array = {1, 2, 3, 4, 5};
    std::vector<int> original = array;
    oblivious_shuffle::shuffle(array);

    // 检查数组长度是否不变
    assert(array.size() == original.size());

    // 检查数组内容是否改变
    bool is_same = true;
    for (size_t i = 0; i < array.size(); ++i) {
        if (array[i] != original[i]) {
            is_same = false;
            break;
        }
    }
    assert(!is_same);

    std::cout << "All tests passed!" << std::endl;
}

int main() {
    test_oblivious_shuffle();
    return 0;
}
