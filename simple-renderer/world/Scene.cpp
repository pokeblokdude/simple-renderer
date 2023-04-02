#include "Scene.h"
#include "Camera.h"
#include "../math/Transform.h"
#include "Object.h"
#include "PointLight.h"

Scene::Scene()
{
    camera = new Camera(this, 50, 1, 0.1f, 1000);
    camera->transform->position.z = -10;
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

