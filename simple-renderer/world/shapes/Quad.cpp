#include "Quad.h"

Quad::Quad()
{
    verts = {
        glm::vec3{ 0.5f,  0.5f, 0},  // 0 - top right
        glm::vec3{-0.5f,  0.5f, 0},  // 1 - top left
        glm::vec3{-0.5f, -0.5f, 0},  // 2 - bottom left
        glm::vec3{ 0.5f, -0.5f, 0}   // 3 - bottom right
    };
    faces = {
        glm::ivec3{0, 1, 2},
        glm::ivec3{0, 2, 3}
    };
}
