test_files = files('state.cpp', 'stack.cpp', 'ref.cpp', 'any.cpp', 'table.cpp')

test_opts = {
  'dependencies': [dependency('gtest'), dependency('gtest_main'), libluacpp_dep],
}

foreach f : test_files
  trunk = '@0@'.format(f).split('/')[-1].split('.')[0]
  nm = 'test_@0@'.format(trunk)
  e = executable(nm, f, kwargs: test_opts)
  test(trunk, e)
endforeach
