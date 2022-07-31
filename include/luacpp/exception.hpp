#pragma once

#include <luacpp/detail/tags.hpp>
#include <stdexcept>

namespace luacpp {

class LuaException : public std::runtime_error {
 public:
  LuaException(detail::tags::state_t* s);

 private:
};
}  // namespace luacpp