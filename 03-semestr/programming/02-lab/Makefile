all: lib main

lib: lib.cpp
	clang++ -std=c++17 -dynamiclib -o liblab.dylib lib.cpp

main: main.cpp
	clang++ -std=c++17 -o main -L./ -llab main.cpp

clean:
	rm *.dylib main