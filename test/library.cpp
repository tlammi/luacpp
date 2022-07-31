#include "luacpp/library.hpp"

#include <gtest/gtest.h>

#include "luacpp/state.hpp"

TEST(Init, Ctor) { luacpp::Library l{"mylib"}; }

TEST(Init, AddLib) {
  luacpp::State s{};
  luacpp::Library mylib{"mylib"};
  s.add_library(std::move(mylib));
}

bool g_foo_called = false;
void foo() { g_foo_called = true; }

TEST(Func, NoArgsVoid) {
  g_foo_called = false;
  luacpp::State s{};
  luacpp::Library mylib{"mylib"};
  mylib.add_function("foo", &foo);
  s.add_library(std::move(mylib));
  ASSERT_FALSE(g_foo_called);
  s.dostring("mylib:foo()");
  ASSERT_TRUE(g_foo_called);
}

TEST(Lambda, NoArgVoid) {
  luacpp::State s{};
  luacpp::Library lib{"lib"};
  bool called = false;
  lib.add_function("f", [&]() { called = true; });
  ASSERT_FALSE(called);
  s.add_library(std::move(lib));
  s.dostring("lib:f()");
  ASSERT_TRUE(called);
}

TEST(MultipleFuncs, NoArgsVoid) {
  luacpp::State s{};
  luacpp::Library lib{"lib"};
  g_foo_called = false;
  lib.add_function("f", &foo);
  bool lambda_called = false;
  lib.add_function("lambda", [&]() { lambda_called = true; });
  s.add_library(std::move(lib));

  ASSERT_FALSE(g_foo_called);
  ASSERT_FALSE(lambda_called);
  s.dostring("lib:f()");
  ASSERT_TRUE(g_foo_called);
  ASSERT_FALSE(lambda_called);
  s.dostring("lib:lambda()");
  ASSERT_TRUE(lambda_called);
}
