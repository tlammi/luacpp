
.PHONY: compile
compile: build
	cd build && ninja

.PHONY: test
test:
	cd build && ninja test

build: build/.tag


build/.tag:
	meson setup build
	touch build/.tag

