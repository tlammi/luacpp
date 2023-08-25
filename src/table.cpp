
#include "cast.hpp"
#include <luacpp/ref.hpp>
#include <luacpp/table.hpp>
#include <stdexcept>

namespace luacpp {

Ref Table::operator[](Int i) {
    (void) to_type_id(lua_rawgeti(cast(m_st), m_idx, i));
    return Ref(m_st, -1);
}

Ref Table::operator[](std::string_view k) {
    lua_pushlstring(cast(m_st), k.data(), k.length());
    (void) to_type_id(lua_rawget(cast(m_st), m_idx));
    return Ref(m_st, -1);
}
} // namespace luacpp
