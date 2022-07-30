#include "luacpp/state.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

// ARG_LUA_DIR comes from command line
const char* LUA_DIR = ARG_LUA_DIR;
const char* LUA_EMPTY = ARG_LUA_DIR "empty.lua";

TEST(Init, Ctor) {
  luacpp::State s{};
  luacpp::State s2{luacpp::flags::open_libs};
}

TEST(DoFile, Existing) {
  luacpp::State s{};
  s.dofile(LUA_EMPTY);
  s.dofile(std::string(LUA_EMPTY));
}

TEST(DoFile, NonExistent) {
  luacpp::State s{};
  ASSERT_ANY_THROW(s.dofile("does-not-exist"));
}

TEST(DoString, Empty) {
  luacpp::State s{};
  s.dostring("");
}

TEST(DoString, Simple) {
  luacpp::State s{luacpp::flags::open_libs};
  static constexpr const char* lua_str = "a = 1; print(a)";
  s.dostring(lua_str);
}

TEST(DoString, NoLibs) {
  luacpp::State s{};
  static constexpr const char* lua_str = "a = a; print(a+1)";
  ASSERT_ANY_THROW(s.dostring(lua_str));
}
