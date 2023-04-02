#pragma once
#include "../math/VectorMath.h"

class PointLight
{
public:
    PointLight();
    ~PointLight();
    
    class Transform* transform;
    vec4 color;
    float intensity;
};
