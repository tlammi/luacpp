#pragma once

#include <bitset>
#include <deque>
#include <luacpp/detail/tags.hpp>
#include <luacpp/library.hpp>
#include <stdexcept>

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

  void dofile(const char* path);
  void dofile(const std::string& path) { dofile(path.c_str()); }

  void dostring(const char* str);
  void dostring(const std::string& str) { dostring(str.c_str()); }

  void add_library(Library&& lib);

  /**
   * Add a global variable to Lua
   *
   * If the symbol does not exist, a new one is created. Existing symbols are
   * overwritten.
   *
   * \tparam Variable (int, double, std::string, ...) or callable. Former
   * creates a variable, latter a function
   * \p name Symbol name
   * \p value Value to store in the symbol
   */
  template <class Val>
  void set_global(const char* name, Val&& value) {
    if constexpr (detail::is_callable_v<Val>) {
      m_global_funcs.emplace_back(
          new detail::FuncImpl{std::forward<Val>(value)});
      set_global_func(name, m_global_funcs.back().get());
    } else {
      detail::push_stack<Val>(m_handle, value);
      push_global(name);
    }
  }

 private:
  void set_global_func(const char* name, detail::Func* f);
  void push_global(const char* name);
  detail::tags::state_t* m_handle;
  std::deque<Library> m_libs{};
  std::deque<std::unique_ptr<detail::Func>> m_global_funcs{};
};

}  // namespace luacpp
