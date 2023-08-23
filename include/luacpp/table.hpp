#pragma once

#include <luacpp/detail/tags.hpp>
#include <luacpp/types.hpp>

#include <cstddef>
#include <string_view>

namespace luacpp {

class Any;

class Table {
  public:
    Table(detail::state_t* st, int idx) : m_st{st}, m_idx{idx} {}

    Any operator[](Int i);
    Any operator[](std::string_view k);


  private:
    detail::state_t* m_st{};
    int m_idx{};
};
} // namespace luacpp
