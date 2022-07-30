#pragma once

#include <luacpp/detail/func.hpp>
#include <memory>
#include <string>
#include <vector>

namespace luacpp {

class Library {
  friend class State;

 public:
  Library(const char* name);
  Library(const Library&) = delete;
  Library& operator=(const Library&) = delete;

  Library(Library&&) = default;
  Library& operator=(Library&&) = default;

  ~Library();

  template <class C>
  void add_function(const char* name, C&& callback) {
    m_functions.emplace_back(name,
                             new detail::FuncImpl(std::forward<C>(callback)));
  }

 private:
  std::string m_name;
  using Vec =
      std::vector<std::pair<std::string, std::unique_ptr<detail::Func>>>;
  Vec m_functions{};
};

}  // namespace luacpp