#pragma once
#include <vector>
#include "../math/VectorMath.h"

class Mesh
{
public:
    std::vector<vec3> verts;
    std::vector<vec3i> faces;
};
