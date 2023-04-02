#include "Object.h"
#include "../math/Transform.h"
#include "Mesh.h"

Object::Object()
{
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


