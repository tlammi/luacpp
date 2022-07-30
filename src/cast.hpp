#pragma once

#include "lua.hpp"
#include "luacpp/detail/tags.hpp"

namespace luacpp {

inline detail::tags::state_t* cast(lua_State* s) {
  return reinterpret_cast<detail::tags::state_t*>(s);
}

inline lua_State* cast(detail::tags::state_t* s) {
  return reinterpret_cast<lua_State*>(s);
}

}  // namespace luacpp
