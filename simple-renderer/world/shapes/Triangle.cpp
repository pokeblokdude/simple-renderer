#include "Triangle.h"
#include <glm/vec3.hpp>

Triangle::Triangle()
{
    verts = {
        glm::vec3{    0,  0.5f, 0},
        glm::vec3{-0.5f, -0.5f, 0},
        glm::vec3{ 0.5f, -0.5f, 0}
    };
    faces = {
        glm::ivec3{0, 1, 2}
    };
}
