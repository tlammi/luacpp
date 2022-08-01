#pragma once

#include <tuple>

namespace luacpp::detail {

template <class... Ts>
struct pack {};

template <class T, class = void>
struct callable_prototype;

template <class T>
struct callable_prototype<T, std::void_t<decltype(&T::operator())>>
    : callable_prototype<decltype(&T::operator())> {};

template <class R, class... Ts>
struct callable_prototype<R (*)(Ts...)> {
  using type = R(Ts...);
};

template <class R, class... Ts>
struct callable_prototype<R(Ts...)> {
  using type = R(Ts...);
};

template <class R, class C, class... Ts>
struct callable_prototype<R (C::*)(Ts...)> {
  using type = R(Ts...);
};

template <class R, class C, class... Ts>
struct callable_prototype<R (C::*)(Ts...) const> {
  using type = R(Ts...);
};

template <class T>
using callable_prototype_t = typename callable_prototype<T>::type;

template <class T>
struct invoke_result_impl;

template <class R, class... Ps>
struct invoke_result_impl<R(Ps...)> {
  using type = R;
};
template <class T>
struct invoke_result {
  using type = typename invoke_result_impl<callable_prototype_t<T>>::type;
};

template <class T>
using invoke_result_t = typename invoke_result<T>::type;

template <class T, class = void>
struct is_callable : std::false_type {};

template <class T>
struct is_callable<T, std::void_t<callable_prototype_t<T>>> : std::true_type {};

template <class T>
constexpr bool is_callable_v = is_callable<T>::value;

template <class T>
struct param_tuple_impl;

template <class R, class... Ps>
struct param_tuple_impl<R(Ps...)> {
  using type = std::tuple<Ps...>;
};

template <class T>
using param_tuple_t = typename param_tuple_impl<callable_prototype_t<T>>::type;

}  // namespace luacpp::detail