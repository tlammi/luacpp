#pragma once

#include <luacpp/detail/tags.hpp>
#include <luacpp/types.hpp>

#include <cstddef>
#include <string_view>

namespace luacpp {

class Ref;

class Table {
  public:
    Ref operator[](Int i);
    Ref operator[](std::string_view k);


  private:
    Table(detail::state_t* st, int idx) : m_st{st}, m_idx{idx} {}
    detail::state_t* m_st{};
    int m_idx{};
};
} // namespace luacpp
