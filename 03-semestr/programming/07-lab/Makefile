CXC = clang++
CARGS = -g -std=c++17 -lpthread

all: mkdir lib build/server

mkdir:
	mkdir -pv build

lib: mkdir server/lib.cpp
	$(CXC) $(CARGS) -dynamiclib -o build/liblab.dylib server/lib.cpp

build/server: mkdir lib server/main.cpp
	$(CXC) $(CARGS) -o build/server -L./build -llab server/main.cpp

clean:
	rm -rf build
	rm *.out