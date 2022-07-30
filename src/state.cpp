#include "luacpp/state.hpp"

#include <stdexcept>

#include "cast.hpp"
#include "lua.hpp"

namespace luacpp {

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

void State::add_library(Library&& lib) {}

}  // namespace luacpp
