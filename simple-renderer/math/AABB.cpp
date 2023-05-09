#include "AABB.h"

AABB::AABB()
{
    min = {0, 0, 0};
    max = {0, 0, 0};
}

AABB::AABB(glm::vec3 min, glm::vec3 max)
{
    this->min = min;
    this->max = max;
}

