test_files = files('state.cpp')

test_opts = {
  'dependencies': [dependency('gtest'), dependency('gtest_main'), libluacpp_dep],
}

foreach f : test_files
  trunk = '@0@'.format(f).split('/')[-1].split('.')[0]
  e = executable(trunk, f, kwargs: test_opts)
  test(trunk, e)
endforeach
