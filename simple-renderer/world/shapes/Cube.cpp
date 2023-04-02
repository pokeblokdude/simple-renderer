#include "Cube.h"
#include "../../math/VectorMath.h"

Cube::Cube()
{
    verts = {
        vec3{ 0.5f,  0.5f, -0.5f},      // 0 - front top right
        vec3{-0.5f,  0.5f, -0.5f},      // 1 - front top left
        vec3{-0.5f, -0.5f, -0.5f},      // 2 - front bottom left
        vec3{ 0.5f, -0.5f, -0.5f},      // 3 - front bottom right
        vec3{ 0.5f,  0.5f,  0.5f},      // 4 - back top right
        vec3{-0.5f,  0.5f,  0.5f},      // 5 - back top left
        vec3{-0.5f, -0.5f,  0.5f},      // 6 - back bottom left
        vec3{ 0.5f, -0.5f,  0.5f}       // 7 - back bottom right
    };
    faces= {
        vec3i{0, 1, 2},     // front
        vec3i{0, 2, 3},     //
        vec3i{0, 4, 1},     // top
        vec3i{4, 5, 1},     //
        vec3i{1, 5, 6},     // left
        vec3i{1, 6, 2},     //
        vec3i{4, 3, 7},     // right
        vec3i{4, 0, 3},     //
        vec3i{3, 2, 6},     // bottom
        vec3i{3, 6, 7},     //
        vec3i{5, 4, 7},     // back
        vec3i{5, 7, 6}      //
    };
}
