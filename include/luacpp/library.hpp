#pragma once

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
    m_functions.emplace_back(name);
  }

 private:
  std::string m_name;
  std::vector<std::string> m_functions{};
};

}  // namespace luacpp