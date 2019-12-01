#include "vec.hpp"

vec3 operator-(vec3 a, vec3 b) {
    return vec3(a.x-b.x, a.y-b.y, a.z-b.z);
}

vec3 operator*(float s, vec3 v) {
    return vec3(s*v.x, s*v.y, s*v.z);
}

vec3 operator/(vec3 v, float s) {
    return (1.f / s) * v;
}

vec3& operator/=(vec3& v, float s)
{
    v.x /= s;
    v.y /= s;
    v.z /= s;
    return v;
}

bool operator==(vec3 a, vec3 b) 
{
    return a.x == b.x && a.y == b.y && a.z == b.z; 
}

vec3 operator-(vec3 v)
{
    return (-1.f) * v;
}

vec3 cross(vec3 a, vec3 b)
{
    return vec3(a.y*b.z - a.z*b.y,
                a.z*b.x - a.x*b.z,
                a.x*b.y - a.y*b.x);
}

float dot(vec3 a, vec3 b)
{
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

float length(vec3 v)
{
    return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
}

vec3 normalize(vec3 v)
{
    return v / length(v);
}

float edgeFunc(vec2 v0, vec2 v1, vec2 p)
{
    return (v0.y - v1.y) * p.x + (v1.x - v0.x) * p.y + v0.x * v1.y - v0.y * v1.x;
}