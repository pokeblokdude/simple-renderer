#include "Triangle.h"
#include <glm/vec3.hpp>

Triangle::Triangle()
{
    verts = {
        {glm::vec3{ 0,     0.5f, 0}, glm::vec3{1.0f,0.0f, 0.0f}},   // top, red
        {glm::vec3{-0.5f, -0.5f, 0}, glm::vec3{0.f, 1.0f, 0.f}},    // bottom left, green
        {glm::vec3{ 0.5f, -0.5f, 0}, glm::vec3{0.f, 0.f, 1.0f}}     // bottom right, blue
    };
    faces = {
        glm::ivec3{0, 1, 2}
    };
}
