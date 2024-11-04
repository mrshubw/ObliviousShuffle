#include <gtest/gtest.h>
#include "psrr.h"

// 测试用的简单 func 函数
void testFunc(uint8_t* input, uint8_t* output) {
    // 将输入的值加一，并写入输出
    *output = *input + 1;
}

// 测试 PSRR 类
class PSRRTest : public ::testing::Test {
protected:
    obl::PSRR psrr;
    uint8_t dummy_examples[10]; // 示例数组
    size_t item_size = sizeof(uint8_t); // 假设我们使用 uint8_t 作为单个数据项
    size_t num_dummy_examples = 10; // 10 个 dummy examples

    PSRRTest() : psrr(1.0, 0.01, 1.0) {}

    void SetUp() override {
        // 初始化 dummy_examples 数组
        for (int i = 0; i < num_dummy_examples; ++i) {
            dummy_examples[i] = static_cast<uint8_t>(i);
        }
    }
};

TEST_F(PSRRTest, ResponseTest) {
    uint8_t output[5]; // 用于存放 response 的输出
    uint8_t input[] = {1, 2, 3, 4, 5};
    size_t num_items = sizeof(input) / sizeof(uint8_t);

    psrr.perturb(dummy_examples, item_size, num_dummy_examples);
    psrr.shuffle(input, num_items);
    psrr.retrieve(testFunc, item_size);
    psrr.response(output); // 进行响应

    // 检查输出是否符合预期
    uint8_t expected_output[5];
    for (size_t i = 0; i < num_items; ++i) {
        expected_output[i] = input[i] + 1; // 计算期望的输出
    }
    
    for (size_t i = 0; i < num_items; ++i) {
        EXPECT_EQ(output[i], expected_output[i]);
    }
}
