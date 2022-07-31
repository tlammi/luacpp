#include "luacpp/detail/func.hpp"

#include "cast.hpp"
#include "lua.hpp"

namespace luacpp::detail {

template <>
std::tuple<int> pop_stack<int>(tags::state_t* state, int idx) {
  return luaL_checkinteger(cast(state), idx);
}

template <>
void push_stack<int>(tags::state_t* s, const int& i) {
  lua_pushinteger(cast(s), i);
}

}  // namespace luacpp::detail