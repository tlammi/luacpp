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

TEST(MultipleLibs, Simple) {
  luacpp::State s{};
  luacpp::Library lib1{"lib1"};
  luacpp::Library lib2{"lib2"};
  int counter = 0;
  lib1.add_function("f", [&]() { ++counter; });
  lib2.add_function("f", [&]() { counter *= 2; });
  s.add_library(std::move(lib1));
  s.add_library(std::move(lib2));

  s.dostring("lib1:f(); lib2:f(); lib2:f(); lib1:f()");
  ASSERT_EQ(counter, 5) << "Skipped functions or invoked in wrong order";
}

TEST(Lambda, IntVoid) {
  luacpp::State s{};
  luacpp::Library l{"lib"};
  int res = 0;
  l.add_function("f", [&](int i) { res = i; });
  s.add_library(std::move(l));
  s.dostring("i=100; lib:f(i)");
  ASSERT_EQ(res, 100);
}

TEST(Lambda, IntIntVoid) {
  luacpp::State s{};
  luacpp::Library l{"lib"};
  int res = 0;
  l.add_function("f", [&](int i, int j) { res = i - j; });
  s.add_library(std::move(l));
  s.dostring("lib:f(100, 99)");
  ASSERT_EQ(res, 1);
}

TEST(Lambda, ReturnValue) {
  luacpp::State s{};
  luacpp::Library l{"lib"};
  int res = 0;
  l.add_function("get", []() -> int { return 42; });
  l.add_function("set", [&](int i) { res = i; });
  s.add_library(std::move(l));
  s.dostring("i = lib:get(); lib:set(i)");
  ASSERT_EQ(res, 42);
}

TEST(Lambda, ReturnTuple) {
  luacpp::State s{};
  luacpp::Library l{"lib"};
  int res = 0;
  l.add_function("get", []() -> std::tuple<int, int> { return {4, 2}; });
  l.add_function("set", [&](int i, int j) { res = 10 * i + j; });
  s.add_library(std::move(l));
  s.dostring("i, j = lib:get(); lib:set(i, j)");
  ASSERT_EQ(res, 42);
}

TEST(Lambda, Strings) {
  luacpp::State s{};
  luacpp::Library l{"lib"};
  l.add_function("gen",
                 [](std::string s, int i) -> std::tuple<std::string, int> {
                   std::string out{};
                   while (i--) out += s;
                   return {out, i};
                 });
  std::string res{};
  l.add_function("validate", [&](std::string s) { res = std::move(s); });

  s.add_library(std::move(l));
  s.dostring(R"(s, _ = lib:gen("foo", 3); lib:validate(s))");
  ASSERT_EQ(res, "foofoofoo");
}