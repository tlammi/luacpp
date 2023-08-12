#include "lua.hpp"
#include <luacpp/types.hpp>
#include <type_traits>

namespace luacpp {

static_assert(std::is_same_v<Int, lua_Integer>);
static_assert(std::is_same_v<Double, lua_Number>);

} // namespace luacpp
