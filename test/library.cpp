#include "luacpp/library.hpp"

#include <gtest/gtest.h>

#include "luacpp/state.hpp"

TEST(Ctor, Init) { luacpp::Library l{"mylib"}; }

void foo() { std::cerr << "foo called :o\n"; }

TEST(Ctor, AddLib) {
  luacpp::State s{};
  luacpp::Library mylib{"mylib"};
  mylib.add_function("foo", &foo);
  s.add_library(std::move(mylib));
  s.dostring("mylib:foo()");
}