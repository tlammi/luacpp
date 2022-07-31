#include "luacpp/detail/func.hpp"

#include <string>

#include "cast.hpp"
#include "lua.hpp"

namespace luacpp::detail {

template <>
std::tuple<int> pop_stack<int>(tags::state_t* state, int idx) {
  return luaL_checkinteger(cast(state), idx);
}

template <>
std::tuple<std::string> pop_stack<std::string>(tags::state_t* state, int idx) {
  size_t len{0};
  const char* str = lua_tolstring(cast(state), idx, &len);
  return {std::string(str, len)};
}

template <>
void push_stack<int>(tags::state_t* s, const int& i) {
  lua_pushinteger(cast(s), i);
}

template <>
void push_stack<std::string>(tags::state_t* s, const std::string& str) {
  lua_pushlstring(cast(s), str.c_str(), str.size());
}

}  // namespace luacpp::detail