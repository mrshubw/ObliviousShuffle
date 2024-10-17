#include <iostream>
#include <vector>
#include <benchmark/benchmark.h>
#include "sorter.h" // 假设这里包含 BitonicSorter 的实现

// Bitonic Sort 流程封装为一个 benchmark 函数
static void BM_BitonicSort(benchmark::State& state) {
    const int array_size = state.range(0);

    // 初始化数组
    std::vector<int> array(array_size);
    for (int i = 0; i < array_size; ++i) {
        array[i] = rand() % 10000; // 用随机数填充数组
    }

    // 创建 BitonicSorter 实例
    obl::BitonicSorter sorter;

    for (auto _ : state) {
        // 每次迭代前都需要重置数据
        std::vector<int> array_copy = array;
        // 调用 Bitonic Sort 的 sort 方法
        sorter.sort(array_copy);
    }
}

// 注册基准测试
BENCHMARK(BM_BitonicSort)->Arg(1000)->Arg(10000)->Arg(100000); // 提供不同大小的数组

// 主函数
BENCHMARK_MAIN();
