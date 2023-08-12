#pragma once

#include <type_traits>
#include <utility>

namespace luacpp::detail {

template <class T>
class [[nodiscard]] Defer {
    static_assert(std::is_nothrow_invocable_v<T>);

  public:
    explicit Defer(T&& t) : m_c{std::move(t)} {}

    Defer(const Defer&) = delete;
    Defer& operator=(const Defer&) = delete;

    Defer(Defer&&) = delete;
    Defer& operator=(Defer&&) = delete;

    ~Defer() {
        m_c();
    }

  private:
    T m_c;
};
} // namespace luacpp::detail
