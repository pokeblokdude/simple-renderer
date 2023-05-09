#pragma once
#include <glm/vec3.hpp>

class AABB
{
public:
    AABB();
    AABB(glm::vec3 min, glm::vec3 max);
    
    glm::vec3 min;
    glm::vec3 max;
};
