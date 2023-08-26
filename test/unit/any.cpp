#include <gtest/gtest.h>
#include <luacpp/any.hpp>

namespace lc = luacpp;

TEST(Any, Default) {
    lc::Any a{};
    ASSERT_FALSE(a);
    ASSERT_TRUE(a.is_nil());
}

TEST(Any, IntRoundTrip) {
    lc::Any a{10};
    ASSERT_TRUE(a.is_num());
    ASSERT_EQ(*a.to_num(), 10);
}

TEST(Any, StringRoundTrip) {
    lc::Any a{"asdf"};
    ASSERT_TRUE(a);
    ASSERT_TRUE(a.is_str());
    ASSERT_EQ(*a.to_str(), "asdf");
}

