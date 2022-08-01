# Lua C++ Bindings

Work in Progress. Currently supported features:
- Libraries
  - Functions
- Global
  - Functions
  - Variables
- Functions (Args...) -> Results...
  - 0 or more arguments
  - 0 or more return values. Multiple return types are handled by returning std::tuples
- Types:
  - int
  - double
  - std::string

Missing features:
- Variadic arguments
- Variadic number of return values
- Parameters with multiple allowed types (e.g. custom type or an int).
- Custom types
- Integer types other than `int`
- Variables in library scope


## Examples

See 'sample/' for examples.

TL;DR:

```C++

#include <iostream>
#include <tuple>
#include <string>

#include <luacpp/luacpp.hpp>

int main(){
    luacpp::State s{luacpp::flags::open_libs}; // open_libs opens the "standard" libraries such as `io` and `math`
    luacpp::Library l{"mylib"};
    l.add_function("get", []() -> std::tuple<int, std::string> {return {42, "foo"};});
    l.add_function("set1", [](int i){std::cerr << i << '\n'; });
    l.add_function("set2", [](std::string s){std::cerr << s << '\n'; });

    s.add_library(std::move(l));
    s.dostring("i, s = mylib.get(); mylib.set1(i); mylib.set2(s)");
}

```
