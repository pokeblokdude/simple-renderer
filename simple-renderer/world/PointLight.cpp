#include "PointLight.h"
#include "../math/Transform.h"

PointLight::PointLight()
{
    transform = new Transform();
    intensity = 1;
    color = {1, 1, 1, 1};
}

PointLight::~PointLight()
{
    delete transform;
}

