#include "image.hpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
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