#include <gtest/gtest.h>
#include <luacpp/ref.hpp>
#include <luacpp/stack.hpp>
#include <luacpp/state.hpp>


class RefTest : public ::testing::Test {
  public:
    RefTest() = default;

  protected:
    luacpp::State state{};
    luacpp::Stack stack{state.stack()};
};

TEST_F(RefTest, EmptyStack) {
    ASSERT_FALSE(stack.ref(1));
    ASSERT_FALSE(stack.ref(2));
    ASSERT_FALSE(stack.ref(3));
}

TEST_F(RefTest, OutOfBounds) {
    stack.push(0);
    stack.push(0);
    stack.push(0);
    stack.push(0);
    ASSERT_FALSE(stack.ref(0));
    ASSERT_FALSE(stack.ref(5));
    ASSERT_TRUE(stack.ref(1));
    ASSERT_TRUE(stack.ref(4));
}

TEST_F(RefTest, RoundTrip) {
    stack.push(1);
    auto ref = stack.ref(1);
    ASSERT_TRUE(ref);
    auto i = ref->to_int();
    ASSERT_TRUE(i);
    ASSERT_EQ(*i, 1);
    auto n = ref->to_num();
    ASSERT_TRUE(n);
    ASSERT_EQ(*n, 1.0);
}

TEST_F(RefTest, StrRoundTrip) {
    stack.push("asdf");
    auto ref = stack.ref(1);
    ASSERT_TRUE(ref);
    ASSERT_EQ(ref->to_str(), "asdf");
}

