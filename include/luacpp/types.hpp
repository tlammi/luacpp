#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <variant>

namespace luacpp {

/**
 * \brief Type IDs for Lua types
 * */
enum class TypeId : uint8_t {
    Nil,
    Bool,
    LightUserdata,
    Number,
    String,
    Table,
    Func,
    Userdata,
    Thread,
    Unknown,
};

TypeId to_type_id(int i);

using Nil = std::nullptr_t;
using Bool = bool;
using Int = long long; // NOLINT
using Double = double;

} // namespace luacpp

