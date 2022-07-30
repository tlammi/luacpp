project('luacpp', 'cpp', 'c', default_options: ['default_library=static']) 

lua_dep = dependency('lua5.4')

INCDIRS = [include_directories('include')]

SRCS = []
subdir('src')

libluacpp = library('luacpp', SRCS, include_directories: INCDIRS + [include_directories('src')], dependencies: lua_dep)
libluacpp_dep = declare_dependency(link_with: libluacpp, include_directories: INCDIRS)

subdir('test')