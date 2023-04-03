#pragma once
#include <vector>

class Scene
{
public:
    Scene();
    ~Scene();

    void CreateCamera(float fov, int width, int height, float near, float far);
    
    std::vector<class Object*> objects;
    std::vector<class PointLight*> lights;
    class Camera* camera;
};
