cmake_minimum_required(VERSION 3.14)
project(ObliviousShuffle)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 递归获取src目录下的所有源文件
file(GLOB_RECURSE SRC src/*.cpp)
# 添加库
add_library(ObliviousShuffle ${SRC})
# 添加头文件目录
target_include_directories(ObliviousShuffle PUBLIC include)

# 启用 SSE、SSE2 和 AES 支持
target_compile_options(ObliviousShuffle PRIVATE
    $<$<CXX_COMPILER_ID:GNU>:-msse -msse2 -maes>   # 对于 GCC 和 Clang
    $<$<CXX_COMPILER_ID:MSVC>:/arch:SSE2>             # 对于 MSVC
)

option(ENABLE_WAKSMAN_SHUFFLE "Enable Waksman Shuffler" OFF)

if(ENABLE_WAKSMAN_SHUFFLE)
    target_compile_definitions(ObliviousShuffle PRIVATE ENABLE_WAKSMAN_SHUFFLE)
endif()


# # 添加测试目录
# add_subdirectory(tests)

# 设置第三方库
# 引入 FetchContent 模块
include(FetchContent)
# 声明并下载 gtest
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2  # 指定 gtest 版本
)
# 下载并准备 gtest
FetchContent_MakeAvailable(googletest)

# 设置单元测试
# 启用CTest功能
include(CTest)
enable_testing()

# 添加测试
add_executable(testSorter tests/test_sorter.cpp)
target_link_libraries(testSorter ObliviousShuffle gtest gtest_main)
add_test(NAME TestSorter COMMAND testSorter)

add_executable(testShuffler tests/test_shuffler.cpp)
target_link_libraries(testShuffler ObliviousShuffle gtest gtest_main)
add_test(NAME TestShuffler COMMAND testShuffler)

add_executable(testOblPrimitives tests/test_obl_primitives.cpp)
target_link_libraries(testOblPrimitives ObliviousShuffle gtest gtest_main)
add_test(NAME TestOblPrimitives COMMAND testOblPrimitives)

add_executable(testPSRR tests/test_psrr.cpp)
target_link_libraries(testPSRR ObliviousShuffle gtest gtest_main)
add_test(NAME TestPSRR COMMAND testPSRR)


# # 设置选项以禁用测试
# set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "")
# # 添加 Google Benchmark
# FetchContent_Declare(
#     benchmark
#     GIT_REPOSITORY https://github.com/google/benchmark.git
#     GIT_TAG        main  # 可以指定具体的版本
# )
# FetchContent_MakeAvailable(benchmark)

# # # 添加性能测试
# add_executable(benchmarks tests/benchmark_bitonic_sorter.cpp)
# target_link_libraries(benchmarks ObliviousShuffle benchmark)
# add_test(NAME BenchmarkBitonicSorter COMMAND benchmarks)