#include "luacpp/state.hpp"

#include <iostream>
#include <stdexcept>

#include "cast.hpp"
#include "lua.hpp"

namespace luacpp {

namespace {

/**
 * Callback called for all lua functions
 *
 * The actual function implementation is stored in upvalues and this callback
 * then calls the actual implementation.
 */
int callback_lua(lua_State* s) {
  detail::Func* ptr =
      static_cast<detail::Func*>(lua_touserdata(s, lua_upvalueindex(1)));
  (*ptr)(cast(s));
  return 0;
}

void create_libtable(lua_State* st, int field_count) {
  luaL_checkversion(st);
  lua_createtable(st, 0, field_count);
}

template <class Iterable>
void publish_functions(lua_State* st, const Iterable& container) {
  for (const auto& [name, func] : container) {
    lua_pushlightuserdata(st, func.get());
    lua_pushcclosure(st, callback_lua, 1);
    lua_setfield(st, -2, name.c_str());
  }
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
  lua_State* st = cast(m_handle);
  const char* modname = lib.m_name.c_str();

  luaL_getsubtable(st, LUA_REGISTRYINDEX, LUA_LOADED_TABLE);
  lua_getfield(st, -1, modname); /* LOADED[modname] */
  if (!lua_toboolean(st, -1)) {  /* package not already loaded? */
    lua_pop(st, 1);              /* remove field */
    create_libtable(st, lib.m_functions.size());
    publish_functions(st, lib.m_functions);
  }
  lua_remove(st, -2);         /* remove LOADED table */
  lua_pushvalue(st, -1);      /* copy of module */
  lua_setglobal(st, modname); /* _G[modname] = module */
}

}  // namespace luacpp
