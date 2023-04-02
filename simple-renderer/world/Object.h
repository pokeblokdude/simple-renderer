#pragma once

class Object
{
public:
    Object();
    Object(class Mesh* mesh);
    ~Object();
    
    class Transform* transform;
    class Mesh* mesh;
};
