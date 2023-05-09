#include "Camera.h"
#include "../math/Transform.h"
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
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

    pixelBuffer = std::vector<std::vector<uint32_t>>(height, std::vector<uint32_t>(width, 0));
}

Camera::~Camera()
{
    delete transform;
}

int Camera::Index(int x, int y) const
{
    return y*width + x;
}

void DrawLine(glm::ivec2 start, glm::ivec2 end)
{
    
}

void Camera::DrawTriangle(std::vector<glm::vec4>* verts, glm::ivec3 face)
{
    for(glm::vec4 vert : *verts)
    {
        pixelBuffer[vert.y][vert.x] = 0xFFFFFFFF;
    }
}

void Camera::RenderSceneToPixels(uint32_t* pixels)
{
    // clear the pixel buffer
    for(int i = 0; i < pixelBuffer.size(); i++)
    {
        for(int j = 0; j < pixelBuffer[i].size(); j++)
        {
            pixelBuffer[i][j] = 0;
        }
    }
    
    const glm::mat4 P = glm::perspective(glm::radians(fov), aspect, nearClip, farClip);
    // lookAt returns NaN when `eye` and `center` are the same value
    // or when `center - eye` and `up` are parallel
    const glm::mat4 V = glm::lookAt(
        transform->position,
        glm::vec3(0, 0, 0),
        glm::vec3(0, 1, 0)
    );
    
    for(Object* obj : owningScene->objects)
    {
        glm::mat4 translate = glm::translate(glm::mat4(1.0f), obj->transform->position);
        glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), 0.f, glm::vec3(0, 1, 0));
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), obj->transform->scale);
        glm::mat4 M = translate * rotate * scale;

        glm::mat4 MVP = P * V * M;
        
        std::vector<glm::vec4> objectVerts;
        objectVerts.reserve(obj->mesh->verts.capacity());
        // apply transformations
        for(glm::vec3 v : obj->mesh->verts)
        {
            glm::vec4 newvert = {v.x, v.y, v.z, 1};
            newvert = MVP * newvert;
            newvert.x = (newvert.x/newvert.w + 1)/2 * width;
            newvert.y = (newvert.y*-1/newvert.w + 1)/2 * height;
            
            objectVerts.push_back(newvert);
        }
        for(glm::ivec3 face : obj->mesh->faces)
        {
            DrawTriangle(&objectVerts, face);
        }
    }

    // write 2d camera buffer to 1d pixel buffer for SDL to draw
    for(int i = 0; i < pixelBuffer.size(); i++)
    {
        for(int j = 0; j < pixelBuffer[i].size(); j++)
        {
            pixels[Index(j, i)] = pixelBuffer[i][j];
        }
    }
}