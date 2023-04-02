#pragma once
#include "./VectorMath.h"

class Transform
{
public:
    vec4 position = {0, 0, 0, 1};
    vec4 scale = {1, 1, 1, 1};
    vec4 rotation = {0, 0, 0, 1};
};
