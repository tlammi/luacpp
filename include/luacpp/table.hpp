#pragma once

#include <luacpp/detail/tags.hpp>
#include <luacpp/types.hpp>

#include <cstddef>
#include <string_view>

namespace luacpp {

namespace table_detail {

template <class T>
constexpr bool use_integer_set_v = std::is_integral_v<std::remove_cvref_t<T>>;


template <class T>
constexpr bool use_generic_set_v = !use_integer_set_v<T>;
} // namespace table_detail

class Ref;
class Stack;

class Table {
    friend class Stack;

  public:
    Ref operator[](Int i);
    Ref operator[](std::string_view k);

    template <class K, class V>
    void rawset(K&& key, V&& val)
        requires table_detail::use_generic_set_v<K>
    {}

    template <class V>
    void rawset(Int i, V&& v);

  private:
    void do_rawset(Int i);
    Table(Stack& stk, int idx) : m_stk{&stk}, m_idx{idx} {}
    Stack* m_stk{};
    int m_idx{};
};


} // namespace luacpp

#include <luacpp/stack.hpp>

namespace luacpp {

template <class V>
void Table::rawset(Int i, V&& v) {
    m_stk->push(std::forward<V>(v));
    do_rawset(i);
}
} // namespace luacpp
