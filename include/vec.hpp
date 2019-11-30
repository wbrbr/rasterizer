#ifndef VEC_HPP
#define VEC_HPP
#include <cmath>

struct vec2 {
    float x, y;

    vec2() : x(0.f), y(0.f) {};
    vec2(float x, float y): x(x), y(y) {}; 
};

struct vec3 {
    float x, y, z;

    vec3() : x(0.f), y(0.f), z(0.f) {};
    vec3(float x, float y, float z): x(x), y(y), z(z) {};

    explicit operator vec2() { return vec2(x, y); };

};

vec3 operator-(vec3 a, vec3 b);
vec3 operator*(float s, vec3 v);
vec3 operator/(vec3 v, float s);
vec3& operator/=(vec3& v, float s);

vec3 cross(vec3 a, vec3 b);
float dot(vec3 a, vec3 b);
float length(vec3 v);
vec3 normalize(vec3 v);

struct vec4 {
    float x, y, z, w;
    vec4(float x, float y, float z, float w): x(x), y(y), z(z), w(w) {};
};

float edgeFunc(vec2 v0, vec2 v1, vec2 p);


#endif