#include "vec.hpp"
#include "image.hpp"
#include <iostream>
#include <random>


const int SAMPLE_COUNT = 10;
const int WIDTH = 500;
const int HEIGHT = 500;

/** Sources:
 * https://fgiesen.wordpress.com/2013/02/06/the-barycentric-conspirac/
**/

void drawTriangle(vec2 v0, vec2 v1, vec2 v2, Image* img)
{
	// TODO: use something better than uniform sampling (jittered ?)
	std::random_device dev;
	std::default_random_engine rng(dev());
	std::uniform_real_distribution<float> dist(0.f, 1.f);
	for (int px = 0; px < WIDTH; px++)
	{
		for (int py = 0; py < HEIGHT; py++)
		{
			int r = 0;
			for (int i = 0; i < SAMPLE_COUNT; i++)
			{
				float offx = dist(rng);
				float offy = dist(rng);
				float x = (float)(px + offx) / (float)WIDTH * 2.f - 1.f;
				float y = (float)(py + offy) / (float)HEIGHT * 2.f - 1.f;
				vec2 p(x, y);

				float w0 = edgeFunc(v1, v2, p);
				float w1 = edgeFunc(v2, v0, p);
				float w2 = edgeFunc(v0, v1, p);
				if (w0 >= 0.f && w1 >= 0.f && w2 >= 0.f) {
					r += 255;
				}
			}

			r /= SAMPLE_COUNT;
			img->set(px, py, r, 0, 0);
		}
	}
}

int main() {

	vec2 v0(0.5f, -0.5f);
	vec2 v1(0.5f, 0.5f);
	vec2 v2(0.f, 0.f);

	Image image(WIDTH, HEIGHT);
	drawTriangle(v0, v1, v2, &image);
	image.write_png("output.png");
	return 0;
}

