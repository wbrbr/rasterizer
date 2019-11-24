#ifndef VEC_HPP
#define VEC_HPP

struct vec2 {
    float x, y;

    vec2() : x(0.f), y(0.f) {};
    vec2(float x, float y): x(x), y(y) {}; 
};

float edgeFunc(vec2 v0, vec2 v1, vec2 p)
{
    return (v0.y - v1.y) * p.x + (v1.x - v0.x) * p.y + v0.x * v1.y - v0.y * v1.x;
}

#endif