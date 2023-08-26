#include <luacpp/stack.hpp>
#include <luacpp/table.hpp>

#include "cast.hpp"
#include <limits>

namespace luacpp {

size_t Stack::size() const noexcept {
    return lua_gettop(cast(m_st));
}


void Stack::push_int(Int i) noexcept {
    lua_pushinteger(cast(m_st), i);
}

void Stack::push_number(Double d) noexcept {
    lua_pushnumber(cast(m_st), d);
}
std::string_view Stack::push_str(std::string_view str) noexcept {
    const char* data = lua_pushlstring(cast(m_st), str.data(), str.size());
    return {data, str.size()};
}

void Stack::push_nil() noexcept {
    lua_pushnil(cast(m_st));
}

Table Stack::push_tbl() noexcept {
    lua_newtable(cast(m_st));
    return Table{*this, to_abs_idx(-1)};
}

std::optional<Int> Stack::to_int(int idx) {
    int is_int{0};
    auto i = lua_tointegerx(cast(m_st), idx, &is_int);
    if (is_int)
        return i;
    return std::nullopt;
}

std::optional<Double> Stack::to_num(int idx) {
    int is_num{0};
    auto num = lua_tonumberx(cast(m_st), idx, &is_num);
    if (is_num)
        return num;
    return std::nullopt;
}

std::string_view Stack::to_str(int idx) {
    size_t len{0};
    const char* dt = lua_tolstring(cast(m_st), idx, &len);
    return {dt, len};
}

void Stack::pop(size_t count) {
    auto sz = size();
    if (count > sz)
        count = sz;
    auto newsz = sz - count;
    if (newsz > std::numeric_limits<int>::max()) {
        newsz = std::numeric_limits<int>::max();
    }
    lua_settop(cast(m_st), static_cast<int>(newsz));
}

std::optional<Ref> Stack::ref(int idx) const {
    if (idx < 1 || static_cast<size_t>(idx) > size()) {
        return std::nullopt;
    }
    return Ref{m_st, idx};
}

int Stack::to_abs_idx(int idx) const noexcept {
    if (idx >= 0)
        return idx;
    int top = lua_gettop(cast(m_st));
    // idx is negative
    return top + idx + 1;
}
} // namespace luacpp
