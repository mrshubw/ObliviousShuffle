#include <vector>
#include <algorithm>
#include <random>
#include <gtest/gtest.h>
#include "sorter.h"

// Function to generate a random array of a given size and type
template <typename T>
std::vector<T> generateRandomArray(int size)
{
    std::vector<T> data(size);                // Create a vector with the specified size
    std::mt19937 gen(std::random_device{}()); // Initialize random number generator

    // Check the type of T and generate corresponding random values
    if constexpr (std::is_same_v<T, int>)
    {
        std::uniform_int_distribution<int> dist(1, 1000); // Integer range
        std::generate(data.begin(), data.end(), [&]()
                      { return dist(gen); }); // Fill the vector with random integers
    }
    else if constexpr (std::is_same_v<T, double>)
    {
        std::uniform_real_distribution<double> dist(1.0, 1000.0); // Floating-point range
        std::generate(data.begin(), data.end(), [&]()
                      { return dist(gen); });
    }
    else if constexpr (std::is_same_v<T, std::string>)
    {
        // String options for random string generation
        std::vector<std::string> options = {"apple", "orange", "banana", "grape", "peach"};
        std::uniform_int_distribution<int> dist(0, options.size() - 1); // Distribution for selecting string options
        std::generate(data.begin(), data.end(), [&]()
                      { return options[dist(gen)]; });
    }

    return data; // Return the generated random array
}

// Template class for sorting test helper
template <typename Sorter>
class SortTestHelper : public testing::Test
{
protected:
    static void SetUpTestCase()
    {
        // Global initialization code, if needed
    }

    static void TearDownTestCase()
    {
        // Global cleanup code, if needed
    }

    void SetUp()
    {
        // Shared initialization code for each test, if needed
    }

    void TearDown()
    {
        // Shared cleanup code for each test, if needed
    }

    // Verify sorting correctness given input and expected output
    template <typename T>
    void verify_sort(const std::vector<T> &input, const std::vector<T> &expected)
    {
        Sorter sorter;
        std::vector<T> copy = input;
        sorter.sort(copy);  
        ASSERT_EQ(copy, expected);
    }

    // Test sorting algorithm on a random array of a specified size
    template <typename T>
    void testRandomArray(int size)
    {
        // Generate a random input array
        std::vector<T> input = generateRandomArray<T>(size);
        // Create an expected output array from the input
        std::vector<T> expected = input;
        // Sort the expected output array using the standard library sort
        std::sort(expected.begin(), expected.end());

        // Verify the sorting result
        verify_sort(input, expected);
    }
};

// Test case for the BitonicSorter with integer type
using BitonicSortIntTest = SortTestHelper<obl::OSorter>;
TEST_F(BitonicSortIntTest, TestRandomArray)
{
    // Define test sizes for integer arrays
    std::vector<int> test_size = {8, 128, 1024, 10, 100, 1000};
    for (int size : test_size)
    {
        // Test sorting algorithm on a random integer array of the given size
        testRandomArray<int>(size);
    }
}
/* 
// Test case for the BitonicSorter with integer type
using BitonicSortIntTest = SortTestHelper<obl::BitonicSorter<int>>;
TEST_F(BitonicSortIntTest, TestRandomArray)
{
    // Define test sizes for integer arrays
    std::vector<int> test_size = {8, 128, 1024, 10, 100, 1000};
    for (int size : test_size)
    {
        // Test sorting algorithm on a random integer array of the given size
        testRandomArray<int>(size);
    }
}

using BitonicSortDoubleTest = SortTestHelper<obl::BitonicSorter<double>>;
TEST_F(BitonicSortDoubleTest, TestRandomArray)
{
    std::vector<int> test_size = {8, 128, 1024, 10, 100, 1000};
    for (int size : test_size)
    {
        testRandomArray<double>(size);
    }
}
 */
// string is not supported by oswap temporarily
// using BitonicSortStringTest = SortTestHelper<obl::BitonicSorter<std::string>>;
// TEST_F(BitonicSortStringTest, TestRandomArray) {
//     // std::vector<int> test_size = {8, 128, 1024, 10, 100, 1000};
//     std::vector<int> test_size = {8};
//     for (int size : test_size) {
//         testRandomArray<std::string>(size);
//     }
// }