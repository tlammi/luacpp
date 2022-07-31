#include "luacpp/library.hpp"

#include <gtest/gtest.h>

#include "luacpp/state.hpp"

TEST(Ctor, Init) { luacpp::Library l{"mylib"}; }

void foo() { std::cerr << "foo called :o\n"; }

TEST(Ctor, AddLib) {
  luacpp::State s{};
  luacpp::Library mylib{"mylib"};
  bool called = false;
  mylib.add_function("foo", [&]() { called = true; });
  s.add_library(std::move(mylib));
  ASSERT_FALSE(called);
  s.dostring("mylib:foo()");
  ASSERT_TRUE(called);
}