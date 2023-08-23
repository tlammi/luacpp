#pragma once

#include "lua.hpp"
#include <luacpp/detail/tags.hpp>

namespace luacpp {

inline detail::state_t* cast(lua_State* s) {
    return reinterpret_cast<detail::state_t*>(s); // NOLINT
}

inline lua_State* cast(detail::state_t* s) {
    return reinterpret_cast<lua_State*>(s); // NOLINT
}

} // namespace luacpp
