all:
	mkdir -p build
	cd build && cmake -DCMAKE_BUILD_TYPE=Debug ..
	cd build && make -j12

run: all
	# exec $(shell find build/ -maxdepth 1 -type f -executable)
	exec build/picture-screensaver-config-panel

release:
	mkdir -p build
	cd build && cmake -DCMAKE_BUILD_TYPE=Release ..
	cd build && make

package: release
	cd build && make package
