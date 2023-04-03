#include "Camera.h"
#include "../math/Transform.h"
#include "../math/VectorMath.h"
#include "./Scene.h"
#include "Mesh.h"
#include "Object.h"

Camera::Camera(Scene* scene, float fov, int width, int height, float near, float far)
{
    owningScene = scene;
    transform = new Transform();
    this->fov = fov;
    this->width = width;
    this->height = height;
    this->aspect = height/(float)width;
    this->nearClip = near;
    this->farClip = far;
}

Camera::~Camera()
{
    delete transform;
}

int Camera::Index(int x, int y) const
{
    return y*width + x;
}

void Camera::DrawTriangle(std::vector<vec4>* verts, vec3i face, uint32_t* pixels)
{
    
}

void Camera::RenderSceneToPixels(uint32_t* pixels)
{
    ModelMatrix();
    ViewMatrix();
    ProjectionMatrix();
    mat4x4 MVP = mul(P, mul(V, M));
    
    for(Object* obj : owningScene->objects)
    {
        std::vector<vec4> objectVerts;
        objectVerts.reserve(obj->mesh->verts.capacity());
        // apply transformations
        for(vec3 v : obj->mesh->verts)
        {
            vec4 newvert = vec4{v.x, v.y, v.z, 1};
            objectVerts.push_back(mul(MVP, newvert));
        }
        for(vec3i face : obj->mesh->faces)
        {
            DrawTriangle(&objectVerts, face, pixels);
        }
    }
}

void Camera::ModelMatrix()
{
    mat4x4 translation = mat4x4 {
        1, 0, 0, transform->position.x,
        0, 1, 0, transform->position.y,
        0, 0, 1, transform->position.z,
        0, 0, 0, 1
    };
    float yrot = radians(transform->rotation.y);
    mat4x4 rotation = mat4x4 {
        cosf(yrot), 0, sinf(yrot), 0,
        0, 1, 0, 0,
        -sinf(yrot), 0, cosf(yrot), 0,
        0, 0, 0, 1
    };
    mat4x4 scale = mat4x4 {
        transform->scale.x, 0, 0, 0,
        0, transform->scale.y, 0, 0,
        0, 0, transform->scale.z, 0,
        0, 0, 0, 1
    };

    M = mul(translation, mul(rotation, scale));
}

void Camera::ViewMatrix()
{
    vec3 eye = vec3{transform->position.x, transform->position.y, transform->position.z};
    vec3 target = vec3{0, 0, 0};
    vec3 up = vec3{0, 1, 0};

    vec3 forward = normalize(eye - target);
    vec3 right = normalize(cross(up, forward));
    vec3 newUp = cross(forward, right);

    mat4x4 view = mat4x4 {
        right.x, newUp.x, forward.x, -dot(right, eye),
        right.y, newUp.y, forward.y, -dot(newUp, eye),
        right.z, newUp.z, forward.z, -dot(forward, eye),
        0, 0, 0, 1
    };

    V = inverse(view);
}

void Camera::ProjectionMatrix()
{
    float e = 1.0f / tanf(fov / 2.0f);
    float f = farClip;
    float n = nearClip;
    float a = aspect;

    M = mat4x4 {
        e / a, 0,           0,             0,
            0, e,           0,             0,
            0, 0, (f+n)/(n-f), 2*(f*n)/(n-f),
            0, 0,          -1,             0
    };
}