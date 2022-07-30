#include "luacpp/state.hpp"

#include <iostream>
#include <stdexcept>

#include "cast.hpp"
#include "lua.hpp"

namespace luacpp {

namespace {

int bar(lua_State* s) {
  std::cerr << "bar called!!!!\n";
  lua_pushstring(s, "foo");
  lua_gettable(s, LUA_REGISTRYINDEX);
  detail::Func* f = (detail::Func*)lua_touserdata(s, -1);
  (*f)(cast(s));
  return 0;
}

constexpr luaL_Reg funcs[] = {{"foo", bar}, {nullptr, nullptr}};

int open_nop(lua_State* s) {
  luaL_newlib(s, funcs);
  return 1;
}

}  // namespace

State::State(flags::StateFlags f) : m_handle{cast(luaL_newstate())} {
  if ((f & flags::open_libs).any()) luaL_openlibs(cast(m_handle));
}

State::State(State&& s) noexcept : m_handle{s.m_handle} {
  s.m_handle = nullptr;
}

State& State::operator=(State&& s) noexcept {
  m_handle = s.m_handle;
  s.m_handle = nullptr;
  return *this;
}

State::~State() {
  if (m_handle) lua_close(cast(m_handle));
}

void State::dofile(const char* path) {
  auto res = luaL_dofile(cast(m_handle), path);
  if (res) throw std::runtime_error("Failed to execute file");
}

void State::dostring(const char* str) {
  auto res = luaL_dostring(cast(m_handle), str);
  if (res) throw std::runtime_error("Failed to execute string");
}

void State::add_library(Library&& lib) {
  lua_pushstring(cast(m_handle), "foo");
  lua_pushlightuserdata(cast(m_handle), lib.m_functions.at(0).second.get());
  lua_settable(cast(m_handle), LUA_REGISTRYINDEX);
  luaL_requiref(cast(m_handle), lib.m_name.c_str(), open_nop, 1);
}

}  // namespace luacpp
