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
    Any() = default;

    Any(const Any& other) = default;
    Any& operator=(const Any& other) = default;

    Any(Any&&) noexcept = default;
    Any& operator=(Any&&) noexcept = default;

    ~Any() {
        using enum TypeId;
        switch (m_id) {
            case Nil:
                std::destroy_at(&m_nil);
                return;
            case Bool:
                std::destroy_at(&m_bool);
                return;
            case TypeId::LightUserdata:
                std::terminate();
            case TypeId::Number:
                std::destroy_at(&m_dbl);
                return;
            case TypeId::String:
                std::destroy_at(&m_str);
                return;
            case TypeId::Table:
            case TypeId::Func:
            case TypeId::Userdata:
            case TypeId::Thread:
            case TypeId::Unknown:
                std::terminate();
                break;
        }
    }

    explicit operator bool() const noexcept {
        return !is_nil();
    }

    [[nodiscard]] bool is_nil() const noexcept {
        return m_id == TypeId::Nil;
    }

    [[nodiscard]] bool is_bool() const noexcept {
        return m_id == TypeId::Bool;
    }

    [[nodiscard]] bool is_number() const noexcept {
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

    [[nodiscard]] std::optional<Double> to_double() const noexcept {
        if (is_number())
            return m_dbl;
        return std::nullopt;
    }

  private:
    union Union {
        Nil m_nil;
        Bool m_bool;
        Double m_dbl;
        std::string_view m_str;
    };

    static_assert(std::is_trivially_copyable_v<Union>);

    TypeId m_id{TypeId::Nil};
};

} // namespace luacpp
