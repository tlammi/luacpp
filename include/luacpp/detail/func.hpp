
#pragma once

#include <luacpp/detail/tags.hpp>
#include <luacpp/detail/type_traits.hpp>
#include <tuple>
#include <utility>

namespace luacpp::detail {

template <class T>
std::tuple<T> pop_stack(tags::state_t* s, int index);

template <class Pack, class Seq>
struct pop_stack_recurse_impl;

template <class... Ts, int... Idxs>
struct pop_stack_recurse_impl<std::tuple<Ts...>,
                              std::integer_sequence<int, Idxs...>> {
  static_assert(sizeof...(Ts) == sizeof...(Idxs));
  static std::tuple<Ts...> func(tags::state_t* s) {
    // No idea why the offset needs to be two instead of one. There seems
    // to be an extra "table" type argumet before other arguments.
    return std::tuple_cat(pop_stack<Ts>(s, Idxs + 2)...);
  }
};

template <class Tuple>
struct pop_stack_recurse
    : pop_stack_recurse_impl<
          Tuple, std::make_integer_sequence<int, std::tuple_size_v<Tuple>>> {};

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
    std::apply(m_c, pop_stack_recurse<Tuple>::func(s));
  }

 private:
  C m_c;
};

}  // namespace luacpp::detail