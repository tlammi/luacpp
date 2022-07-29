#include "luacpp/state.hpp"

#include <gtest/gtest.h>

TEST(State, Ctor) {
  luacpp::State s{};
  luacpp::State s2{luacpp::flags::open_libs};
}
