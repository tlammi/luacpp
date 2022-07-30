#include "luacpp/library.hpp"

#include <gtest/gtest.h>

TEST(Ctor, Init) { luacpp::Library l{"mylib"}; }