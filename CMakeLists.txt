cmake_minimum_required(VERSION 3.10)
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

# 添加测试
enable_testing()
add_executable(tests tests/test_oblivious_shuffle.cpp)
target_link_libraries(tests ObliviousShuffle)
add_test(NAME TestSuite COMMAND tests)

# # 添加性能测试
add_executable(benchmarks benchmarks/benchmark_oblivious_shuffle.cpp)
target_link_libraries(benchmarks ObliviousShuffle)
