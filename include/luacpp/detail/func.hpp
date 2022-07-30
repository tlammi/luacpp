
#pragma once

#include <luacpp/detail/tags.hpp>
#include <luacpp/detail/type_traits.hpp>
#include <tuple>
#include <utility>

namespace luacpp::detail {

template <class T>
std::tuple<T> pop_stack(tags::state_t* s, int index);

template <class T>
struct pop_all_from_stack;

template <class... Ts>
struct pop_all_from_stack<std::tuple<Ts...>> {
  static std::tuple<Ts...> func(tags::state_t* s) {
    int i = 1;
    return std::tuple_cat(pop_stack<Ts>(s, i++)...);
  }
};

class Func {
 public:
  virtual ~Func() {}
  virtual void operator()(tags::state_t*) = 0;

 private:
};

template <class C>
class FuncImpl final : public Func {
 public:
  FuncImpl(C&& c) : m_c{std::forward<C>(c)} {}

  void operator()(tags::state_t* s) override {
    using Tuple = param_tuple_t<std::decay_t<C>>;
    std::apply(m_c, pop_all_from_stack<Tuple>::func(s));
  }

 private:
  C m_c;
};

}  // namespace luacpp::detail