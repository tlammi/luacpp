
#include <luacpp/luacpp.hpp>

int main() {
  luacpp::State s{luacpp::flags::open_libs};  // open_libs initializes
                                              // "standard" libraries in Lua.
  luacpp::Library lib{"lib"};
  lib.add_function("factorial", [](int i) -> int {
    int res = 1;
    while (i > 1) {
      res *= i;
      --i;
    }
    return res;
  });
  s.add_library(std::move(lib));
  s.dostring("i = lib.factorial(10); print(i)");
}