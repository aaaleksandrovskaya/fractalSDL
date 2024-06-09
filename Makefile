OBJS = main.cpp Window.cpp Window.hpp Fractal.cpp Fractal.hpp Mandelbrot.cpp Mandelbrot.hpp
CC = g++
COMPILER_FLAGS = -w -std=c++17
LINKER_FLAGS = -lSDL2
OBJ_NAME = fractal

all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
	
clean:
	rm -f $(OBJ_NAME)
	rm -dfr .vscode
