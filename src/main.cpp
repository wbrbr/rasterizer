#include "vec.hpp"
#include "image.hpp"
#include <iostream>
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

const int WIDTH = 800;
const int HEIGHT = 450;

float* zbuf;

/** Sources:
 * https://fgiesen.wordpress.com/2013/02/06/the-barycentric-conspirac/
**/

// TODO: camera, perspective

void drawTriangle(vec3 v0, vec3 v1, vec3 v2, Image& img)
{
	int xmin = floorf(fmin((v0.x + 1.f) /2.f*(float)WIDTH, fmin((v1.x + 1.f) /2.f*(float)WIDTH, (v2.x + 1.f) /2.f*(float)WIDTH)));
	xmin = xmin >= 0 ? xmin : 0; 
	int xmax = ceilf(fmax((v0.x + 1.f) /2.f*(float)WIDTH, fmax((v1.x + 1.f) /2.f*(float)WIDTH, (v2.x + 1.f) /2.f*(float)WIDTH)));
	xmax = xmax < WIDTH ? xmax : WIDTH-1;
	// TODO: better traversal algorithm
	for (int px = xmin; px <= xmax; px++)
	{
		for (int py = 0; py < HEIGHT; py++)
		{
			vec2 center(((float)px + .5f) / (float)WIDTH * 2.f - 1.f, ((float)py + .5f) / (float)HEIGHT * 2.f - 1.f);
			float w0 = edgeFunc(vec2(v1), vec2(v2), center);
			float w1 = edgeFunc(vec2(v2), vec2(v0), center);
			float w2 = edgeFunc(vec2(v0), vec2(v1), center);
			float s = w0 + w1 + w2;
			w0 /= s;
			w1 /= s;
			w2 /= s;
			float depth = v0.z * w0 + v1.z * w1 + v2.z * w2;
			if (depth < zbuf[py*WIDTH+px] && w0 >= 0 && w1 >= 0 && w2 >= 0) {
				zbuf[py*WIDTH+px] = depth;
				// left handed coordinates
				vec3 n = -normalize(cross(v1 - v0, v2 - v0));
				vec3 lightPos(0.f, 0.f, 0.f);
				vec3 p(center.x, center.y, depth);
				vec3 L = normalize(lightPos - p);
				float ndotl = dot(n, L);
				vec3 col = (ndotl >= 0.f) ? ndotl * vec3(1.f, 1.f, 1.f) : vec3(0.f, 0.f, 0.f);
				img.set(px, py, (unsigned char)(col.x*255.99f), (unsigned char)(col.y*255.99f), (unsigned char)(col.z*255.99f));

				// img.set(px, py, (unsigned char)(w0*255.99f), (unsigned char)(w1*255.99f), (unsigned char)(w2*255.99f));
			}
		}
	}
}

void drawMesh(std::vector<float>& vertices, std::vector<int>& indices, Image& img)
{
	for (unsigned int i = 0; i < indices.size(); i += 3)
	{
		int i0 = indices[i];
		int i1 = indices[i+1];
		int i2 = indices[i+2];
		vec3 v0(vertices[3*i0], vertices[3*i0+1], vertices[3*i0+2]);
		vec3 v1(vertices[3*i1], vertices[3*i1+1], vertices[3*i1+2]);
		vec3 v2(vertices[3*i2], vertices[3*i2+1], vertices[3*i2+2]);


		// vertical fov
		float fov = 30.f * M_PI / 180.f;
		
		// float c = 1.f / tanf(fov/2.f);
		float c = 1.f;

		v0.z = c + 1.f - v0.z;
		v1.z = c + 1.f - v1.z;
		v2.z = c + 1.f - v2.z;

		v0.x /= (c + v0.z) * tanf(fov/2.f);
		v0.y /= (c + v0.z) * tanf(fov/2.f);
		v1.x /= (c + v1.z) * tanf(fov/2.f);
		v1.y /= (c + v1.z) * tanf(fov/2.f);
		v2.x /= (c + v2.z) * tanf(fov/2.f);
		v2.y /= (c + v2.z) * tanf(fov/2.f);

		float aspectinv = (float)HEIGHT/(float)WIDTH;
		v0.x *= aspectinv;
		v1.x *= aspectinv;
		v2.x *= aspectinv;
		// TODO: multiply by proj * view matrices
		drawTriangle(v0, v1, v2, img);
	}
}

int main() {

	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string err;
	tinyobj::LoadObj(&attrib, &shapes, &materials, &err, "suzanne.obj");
	tinyobj::mesh_t mesh = shapes[0].mesh;
	std::vector<int> indices;

	for (unsigned int i = 0; i < mesh.indices.size(); i++)
	{
		indices.push_back(mesh.indices[i].vertex_index);
	}
	Image image(WIDTH, HEIGHT);
	zbuf = new float[WIDTH*HEIGHT];
	for (int i = 0; i < WIDTH * HEIGHT; i++)
	{
		zbuf[i] = +INFINITY;
	}
	std::cout << indices.size() << std::endl;
	drawMesh(attrib.vertices, indices, image);
	image.write_png("output.png");

	delete[] zbuf;
	return 0;
}

