#include "Cube.h"
#include <glm/vec3.hpp>

Cube::Cube()
{
    verts = {
        {glm::vec3{ 0.5f,  0.5f, -0.5f}},      // 0 - front top right
        {glm::vec3{-0.5f,  0.5f, -0.5f}},      // 1 - front top left
        {glm::vec3{-0.5f, -0.5f, -0.5f}},      // 2 - front bottom left
        {glm::vec3{ 0.5f, -0.5f, -0.5f}},      // 3 - front bottom right
        {glm::vec3{ 0.5f,  0.5f,  0.5f}},      // 4 - back top right
        {glm::vec3{-0.5f,  0.5f,  0.5f}},      // 5 - back top left
        {glm::vec3{-0.5f, -0.5f,  0.5f}},      // 6 - back bottom left
        {glm::vec3{ 0.5f, -0.5f,  0.5f}}       // 7 - back bottom right
    };
    faces= {
        glm::ivec3{0, 1, 2},     // front
        glm::ivec3{0, 2, 3},     //
        glm::ivec3{0, 4, 1},     // top
        glm::ivec3{4, 5, 1},     //
        glm::ivec3{1, 5, 6},     // left
        glm::ivec3{1, 6, 2},     //
        glm::ivec3{4, 3, 7},     // right
        glm::ivec3{4, 0, 3},     //
        glm::ivec3{3, 2, 6},     // bottom
        glm::ivec3{3, 6, 7},     //
        glm::ivec3{5, 4, 7},     // back
        glm::ivec3{5, 7, 6}      //
    };
}
