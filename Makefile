INC := -Iinclude
INC += `sdl2-config --cflags`

LIB := `sdl2-config --libs`
LIB += -lSDL2_image -lSDL2_mixer

CXX=g++
CXXFLAGS = -std=c++17 -Wswitch

all:
	${CXX} ${CXXFLAGS} src/*.cpp -g ${INC} ${LIB} -o main

clean:
	rm -f main *.o