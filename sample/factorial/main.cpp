
#include <luacpp/luacpp.hpp>

int main() {
  luacpp::State s{luacpp::flags::open_libs};  // open_libs initializes
                                              // "standard" libraries in Lua.
  s.set_global("factorial", [](int i) -> int {
    int res = 1;
    while (i > 1) {
      res *= i;
      --i;
    }
    return res;
  });
  s.dostring("i = factorial(10); print(i)");
}