#pragma once
#include <vector>

class Scene
{
public:
    Scene();
    ~Scene();
    std::vector<class Object*> objects;
    std::vector<class PointLight*> lights;
    class Camera* camera;
};
