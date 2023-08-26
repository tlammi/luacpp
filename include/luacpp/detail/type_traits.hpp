#pragma once

#include <type_traits>

namespace luacpp::detail {

template <class T>
struct always_false : std::false_type {};

template <class T>
constexpr bool always_false_v = always_false<T>::value;

} // namespace luacpp::detail
