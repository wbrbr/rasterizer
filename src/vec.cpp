#include "vec.hpp"
#include <cstring>

vec2 operator+(vec2 a, vec2 b)
{
    return vec2(a.x + b.x, a.y + b.y);
}

vec2 operator*(float s, vec2 v)
{
    return vec2(s*v.x, s*v.y);
}

vec2 operator/(vec2 v, float s)
{
    return (1.f / s) * v;
}

vec3 operator-(vec3 a, vec3 b) {
    return vec3(a.x-b.x, a.y-b.y, a.z-b.z);
}

vec3 operator*(float s, vec3 v) {
    return vec3(s*v.x, s*v.y, s*v.z);
}

vec3 operator/(vec3 v, float s) {
    return (1.f / s) * v;
}

vec3& operator*=(vec3& v, float s)
{
    v.x *= s;
    v.y *= s;
    v.z *= s;
    return v;
}

vec3& operator/=(vec3& v, float s)
{
    v *= 1.f / s;
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

mat4 mat4::zero()
{
    mat4 m;
    memset(m.m, 0, 16*sizeof(float));
    return m;
}

mat4 mat4::id()
{
    mat4 m = zero();
    m.m[0][0] = 1.f;
    m.m[1][1] = 1.f;
    m.m[2][2] = 1.f;
    m.m[3][3] = 1.f; 
    return m;
}

vec4 operator*(mat4 m, vec4 v)
{
    // ça serait certainement mieux pour le cache si les indices étaient inversés
    return vec4(m.m[0][0] * v.x + m.m[1][0] * v.y + m.m[2][0] * v.z + m.m[3][0] * v.w,
                m.m[0][1] * v.x + m.m[1][1] * v.y + m.m[2][1] * v.z + m.m[3][1] * v.w,
                m.m[0][2] * v.x + m.m[1][2] * v.y + m.m[2][2] * v.z + m.m[3][2] * v.w,
                m.m[0][3] * v.x + m.m[1][3] * v.y + m.m[2][3] * v.z + m.m[3][3] * v.w);
}

mat4 operator*(mat4 a, mat4 b)
{
    mat4 m = mat4::zero();
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                m.m[i][j] += a.m[i][k]*b.m[k][j];
            }
        }
    }
    return m;
}

bool operator==(mat4 a, mat4 b)
{
    bool res = true;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            res &= a.m[i][j] == b.m[i][j];
        }
    }
    return res;
}

mat4 transpose(mat4 m)
{
    mat4 r;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            r.m[i][j] = m.m[j][i];
        }
    }
    return r;
}