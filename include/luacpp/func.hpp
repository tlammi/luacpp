#pragma once

#include <luacpp/detail/tags.hpp>
#include <utility>

namespace luacpp {

class Func {
  public:
    virtual ~Func() = default;


    virtual void operator()(detail::state_t* st) = 0;

  private:
};


template <class F>
class FuncImpl final : public Func {
  public:
    explicit FuncImpl(F&& f) : m_f{std::forward<F>(f)} {}

    void operator()(detail::state_t* st) override {}

  private:
    F m_f;
};
} // namespace luacpp
