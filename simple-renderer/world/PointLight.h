#pragma once
#include <glm/vec4.hpp>

class PointLight
{
public:
    PointLight();
    ~PointLight();
    
    class Transform* transform;
    glm::vec4 color;
    float intensity;
};
