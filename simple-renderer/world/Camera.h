#pragma once
#include <stdint.h>
#include <vector>

#include "../math/VectorMath.h"

class Camera
{
public:
    Camera(class Scene* scene, float fov, int width, int height, float near, float far);
    ~Camera();

    void RenderSceneToPixels(uint32_t* pixels);
    
    class Scene* owningScene;
    class Transform* transform;
    float fov;      // vertical fov
    float aspect;   // w/h
    float farClip;
    float nearClip;
    int width, height;

private:
    mat4x4 M, V, P;
    
    void ModelMatrix();
    void ViewMatrix();
    void ProjectionMatrix();

    void DrawTriangle(std::vector<struct vec4>* verts, struct vec3i face, uint32_t* pixels);
    int Index(int x, int y) const;
};
