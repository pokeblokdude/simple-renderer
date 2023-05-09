#include "Camera.h"
#include "../math/Transform.h"
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "./Scene.h"
#include "Mesh.h"
#include "Object.h"
#include "../math/AABB.h"

Camera::Camera(Scene* scene, float fov, int width, int height, float near, float far)
{
    owningScene = scene;
    transform = new Transform();
    this->fov = fov;
    this->width = width;
    this->height = height;
    this->aspect = width/(float)height;
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

float InsideTriangle(glm::vec2 v0, glm::vec2 v1, glm::vec2 p)
{
    glm::vec2 A = p-v0;
    glm::vec2 B = v1-v0;

    // Zero = point on edge
    // Positive = point right of edge
    // Negative = point left of edge
    return A.x * B.y - A.y * B.x;
}

void Camera::DrawTriangle(std::vector<glm::vec4>* verts, glm::ivec3 face, AABB* bounds)
{
    glm::vec2 v0 = verts->at(face.x);
    glm::vec2 v1 = verts->at(face.y);
    glm::vec2 v2 = verts->at(face.z);

    // setup 2d triangle bounding box
    bounds->min.x = v0.x;
    bounds->min.x = glm::min(bounds->min.x, v1.x);
    bounds->min.x = glm::min(bounds->min.x, v2.x);
    bounds->min.x = glm::max(0.f, bounds->min.x);
    
    bounds->min.y = v0.y;
    bounds->min.y = glm::min(bounds->min.y, v1.y);
    bounds->min.y = glm::min(bounds->min.y, v2.y);
    bounds->min.y = glm::max(0.f, bounds->min.y);

    bounds->max.x = v0.x;
    bounds->max.x = glm::max(bounds->max.x, v1.x);
    bounds->max.x = glm::max(bounds->max.x, v2.x);
    bounds->max.x = glm::min((float)width-1, bounds->max.x);
    
    bounds->max.y = v0.y;
    bounds->max.y = glm::max(bounds->max.y, v1.y);
    bounds->max.y = glm::max(bounds->max.y, v2.y);
    bounds->max.y = glm::min((float)height-1, bounds->max.y);
    
    //glm::vec2 e01 = v1-v0;
    //glm::vec2 e12 = v2-v1;
    //glm::vec2 e20 = v0-v2;

    for(int i = (int)glm::floor(bounds->max.y); i > (int)glm::floor(bounds->min.y); i--)
    {
        for(int j = (int)glm::floor(bounds->min.x); j < (int)glm::floor(bounds->max.x); j++)
        {
            glm::vec2 p(j, i);

            // 2d cross product to determine
            float e0 = InsideTriangle(v1, v0, p);
            float e1 = InsideTriangle(v2, v1, p);
            float e2 = InsideTriangle(v0, v2, p);

            if(e0 >= 0 && e1 >= 0 && e2 >=0)
            {
                pixelBuffer[i][j] = 0xFFFFFFFF;
            }
        }
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
        objectVerts.reserve(obj->mesh->verts.size());
        // apply transformations
        for(glm::vec3 v : obj->mesh->verts)
        {
            glm::vec4 newvert = {v.x, v.y, v.z, 1};
            newvert = MVP * newvert;
            newvert.x = (newvert.x/newvert.w + 1)/2 * width;
            newvert.y = (newvert.y*-1/newvert.w + 1)/2 * height;
            
            objectVerts.push_back(newvert);
        }
        
        AABB* bounds = new AABB();
        for(glm::ivec3 face : obj->mesh->faces)
        {
            DrawTriangle(&objectVerts, face, bounds);
        }
        delete bounds;
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