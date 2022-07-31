#include <luacpp/exception.hpp>

#include "cast.hpp"
#include "lua.hpp"

namespace luacpp {

LuaException::LuaException(detail::tags::state_t* st)
    : std::runtime_error(lua_tostring(cast(st), -1)) {}

}  // namespace luacpp