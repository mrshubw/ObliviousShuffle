#include "bitonic_sort.h"
#include <algorithm>
#include <random>

namespace oblivious_shuffle {
    void shuffle(std::vector<int>& array) {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(array.begin(), array.end(), g);
    }
}
