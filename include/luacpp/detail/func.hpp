
#pragma once

#include <luacpp/detail/tags.hpp>
#include <luacpp/detail/type_traits.hpp>
#include <tuple>
#include <utility>

namespace luacpp::detail {

// TODO: Move to a separate file
template <class T>
std::tuple<T> pop_stack(tags::state_t* s, int index);

// TODO: Move to a separate file
template <class T>
void push_stack(tags::state_t* s, const T& t);

template <class Pack, class Seq>
struct pop_stack_recurse_impl;

template <class... Ts, int... Idxs>
struct pop_stack_recurse_impl<std::tuple<Ts...>,
                              std::integer_sequence<int, Idxs...>> {
  static_assert(sizeof...(Ts) == sizeof...(Idxs));
  static std::tuple<Ts...> func(tags::state_t* s) {
    return std::tuple_cat(pop_stack<Ts>(s, Idxs + 1)...);
  }
};

template <class Tuple>
struct pop_stack_recurse
    : pop_stack_recurse_impl<
          Tuple, std::make_integer_sequence<int, std::tuple_size_v<Tuple>>> {};

template <int Idx, class T>
struct push_recurse {
  static void func(tags::state_t* s, const T& val) { push_stack(s, val); }
};

template <class... Ts, int Idx>
struct push_recurse<Idx, std::tuple<Ts...>> {
  static void func(tags::state_t* s, const std::tuple<Ts...>& val) {
    if constexpr (Idx < sizeof...(Ts)) {
      push_stack(s, std::get<Idx>(val));
      push_recurse<Idx + 1, std::tuple<Ts...>>::func(s, val);
    }
  }
};

template <class Proto>
struct return_value;

template <class... Ps>
struct return_value<void(Ps...)> {
  static constexpr int value = 0;
};

template <class... Ps, class... Rs>
struct return_value<std::tuple<Rs...>(Ps...)> {
  static constexpr int value = sizeof...(Rs);
};

template <class R, class... Ps>
struct return_value<R(Ps...)> {
  static constexpr int value = 1;
};

template <class Proto>
static constexpr int return_value_v = return_value<Proto>::value;

class Func {
 public:
  virtual ~Func() {}
  virtual int operator()(tags::state_t*) = 0;

 private:
};

template <class C>
class FuncImpl final : public Func {
 public:
  FuncImpl(C&& c) : m_c{std::forward<C>(c)} {}

  int operator()(tags::state_t* s) override {
    using Tuple = param_tuple_t<std::decay_t<C>>;
    using Proto = callable_prototype_t<C>;
    if constexpr (!std::is_same_v<invoke_result_t<C>, void>) {
      auto res = std::apply(m_c, pop_stack_recurse<Tuple>::func(s));
      push_recurse<0, decltype(res)>::func(s, res);
    } else {
      std::apply(m_c, pop_stack_recurse<Tuple>::func(s));
    }
    return return_value_v<Proto>;
  }

 private:
  C m_c;
};

}  // namespace luacpp::detail