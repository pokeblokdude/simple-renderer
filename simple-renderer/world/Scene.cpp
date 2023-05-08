#include "Scene.h"
#include "Camera.h"
#include "Object.h"
#include "PointLight.h"
#include "../math/Transform.h"

Scene::Scene()
{
    
}

Scene::~Scene()
{
    for(Object* obj : objects)
    {
        delete obj;
    }
    for(PointLight* l : lights)
    {
        delete l;
    }
    delete camera;
}

void Scene::CreateCamera(float fov, int width, int height, float near, float far)
{
    camera = new Camera(this, fov, width, height, near, far);
    camera->transform->position.z = -10;
}

