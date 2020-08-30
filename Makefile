INC := `sdl2-config --cflags`

LIB := `sdl2-config --libs`
LIB += -lSDL2_image -lSDL2_mixer

compile:
	g++ *.h *.cpp -g $(INC) $(LIB) -o main

clean:
	rm -f main *.o