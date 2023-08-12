#include <gtest/gtest.h>
#include <luacpp/luacpp.hpp>

namespace lp = luacpp;


TEST(State, Ctor) {
    lp::State{};
    lp::State{lp::flags::open_libs};
}


TEST(State, SetGlobal) {
    lp::State s{};
    s.set_global("foo", 100);
    s.set_global("bar", 2.4);
    s.set_global("baz", "foobar");
}

TEST(State, EvalStr) {
    lp::State s{};
    int i = s.evalstr<int>("100");
    ASSERT_EQ(i, 100);
    ASSERT_EQ(s.stack_size(), 0);
}
