#pragma once
#include <glm/vec3.hpp>

class Transform
{
public:
    glm::vec3 position = {0, 0, 0};
    glm::vec3 scale = {1, 1, 1};
    glm::vec3 rotation = {0, 0, 0};

    glm::vec3 Forward() const;
};
