CXC = clang++
CARGS = -g -std=c++17

all: mkdir lib server build/client

mkdir:
	mkdir -pv build

lib: server/lib.cpp
	$(CXC) $(CARGS) -dynamiclib -o build/liblab.dylib server/lib.cpp

server: lib server/main.cpp
	$(CXC) $(CARGS) -o build/server -L./build -llab server/main.cpp

build/client: client/main.cpp
	$(CXC) $(CARGS) -o build/client client/main.cpp

clean:
	rm -rf build