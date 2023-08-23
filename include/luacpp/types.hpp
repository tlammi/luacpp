#pragma once

#include <cstddef>
#include <string>
#include <variant>

namespace luacpp {

/**
 * \brief Type IDs for Lua types
 * */
enum class TypeId {
    Nil,
    Bool,
    LightUserdata,
    Number,
    String,
    Table,
    Func,
    Userdata,
    Thread,
    COUNT_,
};

TypeId to_type_id(int i);

using Nil = std::nullptr_t;
using Bool = bool;
using Int = long long; // NOLINT
using Double = double;

} // namespace luacpp

