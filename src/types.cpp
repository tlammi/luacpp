#include "lua.hpp"
#include <luacpp/types.hpp>
#include <stdexcept>
#include <type_traits>

namespace luacpp {

static_assert(std::is_same_v<Int, lua_Integer>);
static_assert(std::is_same_v<Double, lua_Number>);

TypeId to_type_id(int i) {
    using enum TypeId;
    switch (i) {
        case LUA_TNIL:
            return Nil;
        case LUA_TBOOLEAN:
            return Bool;
        case LUA_TLIGHTUSERDATA:
            return LightUserdata;
        case LUA_TNUMBER:
            return Number;
        case LUA_TSTRING:
            return String;
        case LUA_TTABLE:
            return Table;
        case LUA_TUSERDATA:
            return Userdata;
        case LUA_TTHREAD:
            return Thread;
        default:
            throw std::runtime_error("Invalid type");
    };
}

} // namespace luacpp
