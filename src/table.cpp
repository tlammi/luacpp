
#include "cast.hpp"
#include <luacpp/ref.hpp>
#include <luacpp/table.hpp>
#include <stdexcept>

namespace luacpp {

Ref Table::operator[](Int i) {
    (void) to_type_id(lua_rawgeti(cast(m_stk->raw()), m_idx, i));
    return *m_stk->ref(m_stk->to_abs_idx(-1));
}

Ref Table::operator[](std::string_view k) {
    lua_pushlstring(cast(m_stk->raw()), k.data(), k.length());
    (void) to_type_id(lua_rawget(cast(m_stk->raw()), m_idx));
    return *m_stk->ref(m_stk->to_abs_idx(-1));
}

void Table::do_rawset(Int i) {
    lua_rawseti(cast(m_stk->raw()), m_idx, i);
}

} // namespace luacpp
