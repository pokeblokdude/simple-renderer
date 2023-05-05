#pragma once
#include <vector>
#include <glm/vec3.hpp>

class Mesh
{
public:
    std::vector<glm::vec3> verts;
    std::vector<glm::ivec3> faces;
};
