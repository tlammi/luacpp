#pragma once

#include <luacpp/types.hpp>
#include <optional>
#include <stdexcept>

namespace luacpp {

/**
 * \param Sum type containing any type from Lua
 *
 * This behaves like \a Ref but holds the value directly, not a reference to the stack.
 * \a Ref is kind of a lazily evaluated Any
 * */
class Any {
  public:
    Any() : m_nil{} {}
    explicit Any(Double d) : m_dbl{d}, m_id{TypeId::Number} {}
    explicit Any(std::string_view s) : m_str{s}, m_id{TypeId::String} {}

    Any(const Any& other) = delete;
    Any& operator=(const Any& other) = delete;

    Any(Any&&) noexcept = delete;
    Any& operator=(Any&&) noexcept = delete;

    ~Any();

    explicit operator bool() const noexcept {
        return !is_nil();
    }

    [[nodiscard]] bool is_nil() const noexcept {
        return m_id == TypeId::Nil;
    }

    [[nodiscard]] bool is_bool() const noexcept {
        return m_id == TypeId::Bool;
    }

    [[nodiscard]] bool is_num() const noexcept {
        return m_id == TypeId::Number;
    }

    [[nodiscard]] bool is_str() const noexcept {
        return m_id == TypeId::String;
    }

    [[nodiscard]] TypeId type() const noexcept {
        return m_id;
    }

    [[nodiscard]] std::optional<Nil> to_nil() const noexcept {
        if (is_nil())
            return m_nil;
        return std::nullopt;
    }

    [[nodiscard]] std::optional<Bool> to_bool() const noexcept {
        if (is_bool())
            return m_bool;
        return std::nullopt;
    }

    [[nodiscard]] std::optional<Double> to_num() const noexcept {
        if (is_num())
            return m_dbl;
        return std::nullopt;
    }

    [[nodiscard]] std::optional<std::string_view> to_str() const noexcept {
        if (is_str()) {
            return m_str;
        }
        return std::nullopt;
    }

  private:
    union {
        Nil m_nil;
        Bool m_bool;
        Double m_dbl;
        std::string_view m_str;
    };


    TypeId m_id{TypeId::Nil};
};

} // namespace luacpp
