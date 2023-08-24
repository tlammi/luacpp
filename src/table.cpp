
#include "cast.hpp"
#include <luacpp/ref.hpp>
#include <luacpp/table.hpp>
#include <stdexcept>

namespace luacpp {

Ref Table::operator[](Int i) {
    TypeId type = to_type_id(lua_rawgeti(cast(m_st), m_idx, i));
    using enum TypeId;
    switch (type) {
        case Nil:
            return Ref();
        default:
            throw std::runtime_error("not implemented");
    }
}
Ref Table::operator[](std::string_view k) {
    lua_pushlstring(cast(m_st), k.data(), k.length());
    TypeId type = to_type_id(lua_rawget(cast(m_st), m_idx));
    using enum TypeId;
    switch (type) {
        case Nil:
            return Ref();
        default:
            throw std::runtime_error("not implemented");
    }
}
} // namespace luacpp
