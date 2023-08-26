#include <gtest/gtest.h>

#include <luacpp/luacpp.hpp>

namespace lc = luacpp;


class StackTest : public ::testing::Test {
  protected:
    lc::State state{};
    lc::Stack stack{state.stack()};
};

TEST_F(StackTest, Empty) {
    ASSERT_EQ(stack.size(), 0);
    ASSERT_EQ(stack.length(), 0);
    ASSERT_EQ(stack.to_abs_idx(-1), 0);
    ASSERT_TRUE(stack.empty());
}

TEST_F(StackTest, Push) {
    stack.push(100);
    ASSERT_EQ(stack.size(), 1);
    ASSERT_EQ(stack.length(), 1);
    ASSERT_EQ(stack.to_abs_idx(-1), 1);
    ASSERT_EQ(stack.to_abs_idx(-2), 0);
    ASSERT_FALSE(stack.empty());
}

TEST_F(StackTest, PushPull) {
    stack.push(1.0);
    ASSERT_EQ(stack.size(), 1);
    auto res = stack.to_num(-1);
    ASSERT_TRUE(res);
    ASSERT_EQ(*res, 1.0);
    stack.pop();
    ASSERT_EQ(stack.size(), 0);
}

TEST_F(StackTest, StringRoundTrip) {
    stack.push("foobar");
    ASSERT_EQ(stack.size(), 1);
    auto res = stack.to_str(-1);
    ASSERT_EQ(res, "foobar");
}

TEST_F(StackTest, NumToStr) {
    stack.push(1.0);
    auto res = stack.to_str(-1);
    ASSERT_EQ(res, "1.0");
}

TEST_F(StackTest, NilToStr) {
    stack.push_nil();
    auto res = stack.to_str(-1);
    ASSERT_EQ(res, "");
}
