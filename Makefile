CFLAGS = -Wall -Wextra -Iinclude/ -g -Og

all: main.o image.o vec.o
	g++ $(CFLAGS) $^ -o rasterizer

%.o: src/%.cpp
	g++ $(CFLAGS) -c $< -o $@

run: all
	./rasterizer
	gpicview output.png
