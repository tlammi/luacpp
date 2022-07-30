

test_deps = [dependency('gtest'), dependency('gtest_main'), libluacpp_dep]

this_dir = meson.current_source_dir()

test_state = executable('test_state', 'state.cpp', dependencies: test_deps, cpp_args: ['-DARG_LUA_DIR="' + this_dir + '/lua/"'])
test_lib = executable('test_lib', 'library.cpp', dependencies: test_deps)

test('State', test_state)
test('Library', test_lib)
