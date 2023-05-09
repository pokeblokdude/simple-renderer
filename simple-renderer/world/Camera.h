#pragma once
#include <stdint.h>
#include <vector>

#include <glm/mat4x4.hpp>

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

    uint32_t clearColor;

private:
    std::vector<std::vector<uint32_t>> colorBuffer;
    std::vector<std::vector<uint8_t>> depthBuffer;

    class AABB* renderBounds;
    
    void DrawTriangle(std::vector<class glm::vec4>* verts, std::vector<class glm::vec3>* colors, class glm::ivec3 face);
    int Index(int x, int y) const;
};
