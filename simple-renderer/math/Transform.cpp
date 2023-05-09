#include "Transform.h"

#include <glm/detail/func_trigonometric.inl>

glm::vec3 Transform::Forward() const
{
    glm::vec3 forward(
        glm::cos(rotation.x) * glm::sin(rotation.y),
        -glm::sin(rotation.x),
        glm::cos(rotation.x) * glm::cos(rotation.y)
    );
    return forward;
}
