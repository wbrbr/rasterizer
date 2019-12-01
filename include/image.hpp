#ifndef IMAGE_HPP
#define IMAGE_HPP
#include <string>
#include "vec.hpp"

class Image
{
public:
    static Image load(std::string path);
    
    Image(int width, int height);
    ~Image();
    void write_png(std::string path);

    // positive y is up
    void set(int x, int y, unsigned char r, unsigned char g, unsigned char b);
    vec3 get(int x, int y);
    int getWidth();
    int getHeight();

private:
    int width;
    int height;
    unsigned char* buf;
};
#endif