#ifndef MESH_HPP
#define MESH_HPP
#include <vector>
#include "vec.hpp"


struct Mesh {
    std::vector<int> vert_indices;
    std::vector<int> uv_indices;
    std::vector<vec3> vertices;
    std::vector<vec2> texcoords;
};
#endif