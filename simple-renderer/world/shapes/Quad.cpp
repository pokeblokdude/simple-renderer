#include "Quad.h"

Quad::Quad()
{
    verts = {
        {glm::vec3{ 0.5f,  0.5f, 0}, glm::vec3{1.0f, 0.f, 0.f}},  // 0 - top right
        {glm::vec3{-0.5f,  0.5f, 0}, glm::vec3{1.0f, 1.0f, 0.f}},  // 1 - top left
        {glm::vec3{-0.5f, -0.5f, 0}, glm::vec3{0.f, 1.0f, 0.f}},  // 2 - bottom left
        {glm::vec3{ 0.5f, -0.5f, 0}, glm::vec3{0.f, 0.f, 1.0f}}   // 3 - bottom right
    };
    faces = {
        glm::ivec3{0, 1, 2},
        glm::ivec3{0, 2, 3}
    };
}
