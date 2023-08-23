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

    i += s.evalstr<int>("1 + 3");
    ASSERT_EQ(i, 104);
    ASSERT_EQ(s.stack_size(), 0);
}

TEST(DoStr, Empty) {
    lp::State s{};
    s.dostr("");
}

TEST(DoStr, CallFunc) {
    lp::State s{};
    s.dostr(R"(
function add(x, y)
  return x + y
end
x = 100
y = 12
z = add(x, y)
)");
}

TEST(DoStr, GlobalRoundTrip) {
    lp::State s{};
    s.set_global("x", 1);
    s.dostr("x = x + 10");
    auto x = s.get_global<lp::Int>("x");
    ASSERT_EQ(x, 11);
}

