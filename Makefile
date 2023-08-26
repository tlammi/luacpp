
.PHONY: compile
compile: build
	cd build && ninja

.PHONY: test
test: build/.tag
	cd build && ninja test

.PHONY: clean
clean:
	rm -rf build

build: build/.tag


build/.tag:
	meson setup -Db_sanitize=address -Db_lundef=false build
	touch build/.tag

