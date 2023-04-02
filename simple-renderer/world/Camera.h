#pragma once
#include <stdint.h>

class Camera
{
public:
    Camera(class Scene* scene, float fov, float aspect, float near, float far);
    ~Camera();

    void RenderSceneToPixels(uint32_t* pixels);

    class Scene* owningScene;
    class Transform* transform;
    float fov;      // vertical fov
    float aspect;   // w/h
    float farClip;
    float nearClip;
};
