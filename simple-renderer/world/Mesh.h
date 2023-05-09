#pragma once
#include <vector>
#include <glm/vec3.hpp>
#include "Vertex.h"

class Mesh
{
public:
    std::vector<Vertex> verts;
    std::vector<glm::ivec3> faces;
};
