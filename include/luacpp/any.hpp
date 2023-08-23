#pragma once

#include <luacpp/types.hpp>
#include <optional>
#include <stdexcept>

namespace luacpp {
/**
 * \param Sum type containing any type from Lua
 * */
class Any {
  public:
    Any() : m_nil{} {}

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
                throw std::runtime_error("not implemented");
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
            case TypeId::COUNT_:
                throw std::runtime_error("not implemented");
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
    union {
        Nil m_nil;
        Bool m_bool;
        Double m_dbl;
        std::string_view m_str;
    };

    TypeId m_id{TypeId::Nil};
};

} // namespace luacpp
