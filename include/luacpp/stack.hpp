#pragma once

#include <cstddef>
#include <luacpp/detail/tags.hpp>
#include <luacpp/ref.hpp>
#include <luacpp/types.hpp>
#include <optional>

namespace luacpp {

class Table;

class Stack {
    friend class State;

  public:
    [[nodiscard]] size_t size() const noexcept;
    [[nodiscard]] size_t length() const noexcept {
        return size();
    }

    [[nodiscard]] bool empty() const noexcept {
        return size() == 0;
    }


    template <class T>
    void push(T&& t) noexcept
        requires std::is_integral_v<T>
    {
        push_int(std::forward<T>(t));
    }

    template <class T>
    void push(T&& t) noexcept
        requires std::is_floating_point_v<T>
    {
        push_number(std::forward<T>(t));
    }

    std::string_view push(std::string_view str) noexcept {
        return push_str(str);
    }

    void push(std::nullptr_t /*unused*/) noexcept {
        return push_nil();
    }

    void push_int(Int i) noexcept;
    void push_number(Double d) noexcept;
    std::string_view push_str(std::string_view str) noexcept;
    void push_nil() noexcept;
    Table push_tbl() noexcept;

    std::optional<Int> to_int(int idx);
    std::optional<Double> to_num(int idx);
    std::string_view to_str(int idx);


    void pop(size_t count = 1);


    /**
     * \brief Convert relative (or abs) index to an absolute.
     *
     * E.g. converts -1 to lua_gettop() while leaves non-negative values untouched
     * */
    [[nodiscard]] int to_abs_idx(int idx) const noexcept;


    [[nodiscard]] std::optional<Ref> ref(int idx) const;

    detail::state_t* raw() noexcept {
        return m_st;
    }

  private:
    explicit Stack(detail::state_t& st) : m_st{&st} {}

    detail::state_t* m_st;
};
} // namespace luacpp
