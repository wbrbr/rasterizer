CFLAGS = -Wall -Wextra -Iinclude/

all: main.o image.o
	g++ $(CFLAGS) $^ -o rasterizer

%.o: src/%.cpp
	g++ $(CFLAGS) -c $< -o $@

run: all
	./rasterizer
	gpicview output.png
