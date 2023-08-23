#include "cast.hpp"

#include <lauxlib.h>
#include <lua.h>
#include <luacpp/state.hpp>
#include <lualib.h>

namespace luacpp {

State::State(StateFlags opts) : m_st{cast(luaL_newstate())} {
    if ((opts & flags::open_libs).any()) {
        luaL_openlibs(cast(m_st));
    }
}

State::State(State&& other) noexcept {
    std::swap(m_st, other.m_st);
}

State& State::operator=(State&& other) noexcept {
    std::swap(m_st, other.m_st);
    return *this;
}

State::~State() {
    if (m_st)
        lua_close(cast(m_st));
}

void State::dofile(const char* path) {
    luaL_dofile(cast(m_st), path);
}

void State::dostr(const char* str) {
    luaL_dostring(cast(m_st), str);
}

size_t State::stack_size() const noexcept {
    return lua_gettop(cast(m_st));
}

#if defined(LUACPP_LUA_HANDLE)
lua_State* State::lua_state() const noexcept {
    return cast(m_st);
}
#endif

void State::loadstring(const char* str) {
    luaL_loadstring(cast(m_st), str);
}

void State::pcall(int nargs, int nres) {
    lua_pcall(cast(m_st), nargs, nres, 0);
}


void State::set_global_int(const char* name, Int i) {
    lua_pushinteger(cast(m_st), i);
    lua_setglobal(cast(m_st), name);
}

void State::set_global_float(const char* name, Double d) {
    lua_pushnumber(cast(m_st), d);
    lua_setglobal(cast(m_st), name);
}

void State::set_global_str(const char* name, std::string_view s) {
    lua_pushlstring(cast(m_st), s.data(), s.length());
    lua_setglobal(cast(m_st), name);
}

void State::get_global_to_stack(const char* name) {
    lua_getglobal(cast(m_st), name);
}

std::optional<Int> State::pop_stack_int() {
    int is_int{false};
    auto i = lua_tointegerx(cast(m_st), -1, &is_int);
    if (is_int) {
        lua_pop(cast(m_st), 1);
        return i;
    }
    return std::nullopt;
}

std::optional<Double> State::pop_stack_float() {
    int is_num{false};
    auto d = lua_tonumberx(cast(m_st), -1, &is_num);
    if (is_num) {
        lua_pop(cast(m_st), 1);
        return d;
    }
    return std::nullopt;
}

std::string State::pop_stack_str() {
    size_t len{0};
    const auto* s = lua_tolstring((cast(m_st)), -1, &len);
    std::string res(s, len);
    lua_pop(cast(m_st), 1);
    return res;
}

} // namespace luacpp
