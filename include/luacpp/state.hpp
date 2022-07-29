#pragma once

#include <bitset>
#include <luacpp/detail/tags.hpp>

namespace luacpp {
namespace flags {
using StateFlags = std::bitset<1>;
inline constexpr StateFlags open_libs = 0b1;
}  // namespace flags

class State {
 public:
  explicit State(flags::StateFlags f = 0);
  State(const State&) = delete;
  State& operator=(const State&) = delete;

  State(State&&) noexcept;
  State& operator=(State&&) noexcept;
  ~State();

 private:
  detail::tags::state_t* m_handle;
};

}  // namespace luacpp
