#include "luacpp/state.hpp"

#include <stdexcept>

extern "C" {
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
}

namespace luacpp {
namespace {
detail::tags::state_t* cast(lua_State* s) {
  return reinterpret_cast<detail::tags::state_t*>(s);
}

lua_State* cast(detail::tags::state_t* s) {
  return reinterpret_cast<lua_State*>(s);
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
}  // namespace luacpp
