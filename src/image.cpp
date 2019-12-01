#include "image.hpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

Image::Image(int width, int height): width(width), height(height) 
{
    buf = new unsigned char[3*width*height];
    memset(buf, 0, 3*width*height);
    stbi_flip_vertically_on_write(true);
}

Image::~Image()
{
    delete[] buf;
}

Image Image::load(std::string file)
{
    int w, h;    
    stbi_set_flip_vertically_on_load(true);
    unsigned char* buf = stbi_load(file.c_str(), &w, &h, NULL, 3);
    if (buf == nullptr) {
        std::cerr << "Failed to write read " << file << ": " << stbi_failure_reason() <<  std::endl;
        exit(1);  
    }

    Image img(w, h);
    memcpy(img.buf, buf, w*h*3);
    stbi_image_free(buf);
    // std::cout << img.buf[]

    return img;
}

void Image::write_png(std::string path)
{
    if (!stbi_write_png(path.c_str(), width, height, 3, buf, 0)) {
        std::cerr << "Failed to write to " << path << ": " << std::endl;
        exit(1);  
    }
}

void Image::set(int x, int y, unsigned char r, unsigned char g, unsigned char b)
{
    int i = y*width+x;
    buf[3*i] = r;
    buf[3*i+1] = g;
    buf[3*i+2] = b;
}

vec3 Image::get(int x, int y)
{
    int i = y*width+x;
    vec3 c;
    c.x = (float)buf[3*i] / 255.f;
    c.y = (float)buf[3*i+1] / 255.f;
    c.z = (float)buf[3*i+2] / 255.f;
    return c;
}

int Image::getWidth()
{
    return width;
}

int Image::getHeight()
{
    return height;
}