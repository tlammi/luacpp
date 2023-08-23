#pragma once

#include <luacpp/detail/tags.hpp>
#include <memory>
#include <utility>

namespace luacpp {

// TODO: Implement
template <class T>
class Userdata {
  public:
    Userdata(const Userdata&) = delete;
    Userdata& operator=(const Userdata&) = delete;

    Userdata(Userdata&& other) noexcept {
        std::swap(m_ptr, other.m_ptr);
    }

    Userdata& operator=(Userdata&& other) noexcept {
        std::swap(m_ptr, other.m_ptr);
        return *this;
    }
    ~Userdata() = default;

    T& operator*() noexcept {
        return *m_ptr;
    }

    const T& operator*() const noexcept {
        return *m_ptr;
    }

    T* operator->() noexcept {
        return m_ptr;
    }

    const T* operator->() const noexcept {
        return m_ptr;
    }

  private:
    explicit Userdata(T* ptr) : m_ptr{ptr} {}

    T* m_ptr{};
};

/*
 * Userdata<Array> new_array(State* st, size_t count){
 *    return st->userdata<Array>(count);
 * }
 * */

} // namespace luacpp
