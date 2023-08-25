#include <luacpp/ref.hpp>

#include "cast.hpp"

namespace luacpp {

bool Ref::is_nil() const noexcept {
    return lua_isnil(cast(m_st), m_idx);
}
bool Ref::is_int() const noexcept {
    return lua_isinteger(cast(m_st), m_idx);
}
bool Ref::is_num() const noexcept {
    return lua_isnumber(cast(m_st), m_idx);
}
bool Ref::is_str() const noexcept {
    return lua_isstring(cast(m_st), m_idx);
}

TypeId Ref::type_id() const noexcept {
    return to_type_id(lua_type(cast(m_st), m_idx));
}

std::optional<Int> Ref::to_int() const noexcept {
    int is_int{0};
    auto i = lua_tointegerx(cast(m_st), m_idx, &is_int);
    if (is_int)
        return i;
    return std::nullopt;
}

std::optional<Double> Ref::to_num() const noexcept {
    int is_num{0};
    auto num = lua_tonumberx(cast(m_st), m_idx, &is_num);
    if (is_num)
        return num;
    return std::nullopt;
}

std::string_view Ref::to_str() const noexcept {
    size_t len{0};
    const char* dt = lua_tolstring(cast(m_st), m_idx, &len);
    return {dt, len};
}

Ref::Ref(detail::state_t* st, int idx) : m_st{st}, m_idx{idx} {}
} // namespace luacpp
