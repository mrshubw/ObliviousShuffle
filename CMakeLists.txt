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

# 添加测试目录
add_subdirectory(tests)
