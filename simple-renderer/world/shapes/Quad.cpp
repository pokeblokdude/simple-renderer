#include "Quad.h"

Quad::Quad()
{
    verts = {
        vec3{ 0.5f,  0.5f, 0},  // 0 - top right
        vec3{-0.5f,  0.5f, 0},  // 1 - top left
        vec3{-0.5f, -0.5f, 0},  // 2 - bottom left
        vec3{ 0.5f, -0.5f, 0}   // 3 - bottom right
    };
    faces = {
        vec3i{0, 1, 2},
        vec3i{0, 2, 3}
    };
}
