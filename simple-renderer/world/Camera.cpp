#include "Camera.h"
#include "../math/Transform.h"
#include "./Scene.h"

Camera::Camera(Scene* scene, float fov, float aspect, float near, float far)
{
    owningScene = scene;
    transform = new Transform();
    this->fov = fov;
    this->aspect = aspect;
    this->nearClip = near;
    this->farClip = far;
}

Camera::~Camera()
{
    delete transform;
}

void Camera::RenderSceneToPixels(uint32_t* pixels)
{
    // TODO: render scene :)
}



