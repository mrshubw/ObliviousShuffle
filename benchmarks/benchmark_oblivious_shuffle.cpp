#include <iostream>
#include <vector>
#include <chrono>
#include "bitonic_sort.h"

void benchmark_oblivious_shuffle() {
    const int num_iterations = 1000;
    const int array_size = 10000;

    std::vector<int> array(array_size);
    for (int i = 0; i < array_size; ++i) {
        array[i] = i;
    }

    auto start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < num_iterations; ++i) {
        oblivious_shuffle::shuffle(array);
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    std::cout << "Shuffling " << array_size << " elements " << num_iterations << " times took "
              << duration.count() << " microseconds." << std::endl;
}

int main() {
    benchmark_oblivious_shuffle();
    return 0;
}
