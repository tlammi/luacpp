#pragma once

#include <luacpp/detail/tags.hpp>
#include <luacpp/types.hpp>
#include <optional>

namespace luacpp {


/**
 * Reference to a value in Lua stack
 * */
class Ref {
    friend class Stack;
    friend class Table;

  public:
    explicit operator bool() const noexcept {
        return !is_nil();
    }

    [[nodiscard]] bool is_nil() const noexcept;
    [[nodiscard]] bool is_int() const noexcept;
    [[nodiscard]] bool is_num() const noexcept;
    [[nodiscard]] bool is_str() const noexcept;

    [[nodiscard]] TypeId type_id() const noexcept;


    [[nodiscard]] std::optional<Int> to_int() const noexcept;
    [[nodiscard]] std::optional<Double> to_num() const noexcept;
    [[nodiscard]] std::string_view to_str() const noexcept;


  private:
    Ref(detail::state_t* st, int idx);

    detail::state_t* m_st;
    int m_idx;
};
} // namespace luacpp
