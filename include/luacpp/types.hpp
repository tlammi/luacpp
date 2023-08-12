#pragma once

#include <cstddef>
#include <string>
#include <variant>

namespace luacpp {

/**
 * \brief Type IDs for Lua types
 * */
enum class TypeId {
    Nil,
    Bool,
    LightUserData,
    Number,
    String,
    Table,
    Func,
    UserData,
    Thread,
    COUNT_,
};

using Nil = std::nullptr_t;
using Bool = bool;
using Int = long long; // NOLINT
using Double = double;

/**
 * \param Sum type containing any type from Lua
 * */
class Any {
  public:
    Any() = default;

    explicit operator bool() const noexcept {
        return !is_nil();
    }

    [[nodiscard]] bool is_nil() const noexcept {
        return std::holds_alternative<Nil>(m_var);
    }

    [[nodiscard]] bool is_bool() const noexcept {
        return std::holds_alternative<Bool>(m_var);
    }

    [[nodiscard]] bool is_number() const noexcept {
        return std::holds_alternative<Double>(m_var);
    }


    [[nodiscard]] bool is_str() const noexcept {
        return std::holds_alternative<std::string>(m_var);
    }

    [[nodiscard]] TypeId type() const noexcept {
        using T = TypeId;
        if (is_nil())
            return T::Nil;
        if (is_bool())
            return T::Bool;
        if (is_number())
            return T::Number;
        if (is_str())
            return T::String;
        return T::Nil;
    }

  private:
    using Variant = std::variant<Nil, Bool, Double, std::string>;

    Variant m_var{};
};

} // namespace luacpp

