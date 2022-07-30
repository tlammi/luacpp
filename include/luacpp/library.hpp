#pragma once

namespace luacpp {

class Library {
 public:
  Library(const char* name);
  Library(const Library&) = delete;
  Library& operator=(const Library&) = delete;

  Library(Library&&) = default;
  Library& operator=(Library&&) = default;

  ~Library();

  template <class C>
  void add_function(const char* name, C&& callback) {}

 private:
};

}  // namespace luacpp