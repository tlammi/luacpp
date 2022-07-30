#include "luacpp/library.hpp"

#include "cast.hpp"
#include "lua.hpp"

namespace luacpp {

Library::Library(const char* name) : m_name{name} {}
Library::~Library() {}

}  // namespace luacpp