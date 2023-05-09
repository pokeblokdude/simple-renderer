#include "Object.h"
#include "../math/Transform.h"
#include "Mesh.h"

Object::Object()
{
    transform = new Transform();
    mesh = nullptr;
}

Object::Object(Mesh* mesh)
{
    transform = new Transform();
    this->mesh = mesh;
}

Object::~Object()
{
    delete mesh;
    delete transform;
}


