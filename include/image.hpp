#ifndef IMAGE_HPP
#define IMAGE_HPP
#include <string>

class Image
{
public:
    Image(int width, int height);
    ~Image();
    void write_png(std::string path);

    // positive y is up
    void set(int x, int y, unsigned char r, unsigned char g, unsigned char b);

private:
    int width;
    int height;
    unsigned char* buf;
};
#endif