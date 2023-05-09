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

    colorBuffer = std::vector<std::vector<uint32_t>>(height, std::vector<uint32_t>(width, 0));
    depthBuffer = std::vector<std::vector<uint8_t>>(height, std::vector<uint8_t>(width, 0));

    renderBounds = new AABB();
}

Camera::~Camera()
{
    delete transform;
    delete renderBounds;
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

void Camera::DrawTriangle(std::vector<glm::vec4>* verts, std::vector<glm::vec3>* colors, glm::ivec3 face)
{
    glm::vec2 v0 = verts->at(face.x);
    glm::vec2 v1 = verts->at(face.y);
    glm::vec2 v2 = verts->at(face.z);

    // setup 2d triangle bounding box
    renderBounds->min.x = v0.x;
    renderBounds->min.x = glm::min(renderBounds->min.x, v1.x);
    renderBounds->min.x = glm::min(renderBounds->min.x, v2.x);
    renderBounds->min.x = glm::max(0.f, renderBounds->min.x);
    
    renderBounds->min.y = v0.y;
    renderBounds->min.y = glm::min(renderBounds->min.y, v1.y);
    renderBounds->min.y = glm::min(renderBounds->min.y, v2.y);
    renderBounds->min.y = glm::max(0.f, renderBounds->min.y);

    renderBounds->max.x = v0.x;
    renderBounds->max.x = glm::max(renderBounds->max.x, v1.x);
    renderBounds->max.x = glm::max(renderBounds->max.x, v2.x);
    renderBounds->max.x = glm::min((float)width-1, renderBounds->max.x);
    
    renderBounds->max.y = v0.y;
    renderBounds->max.y = glm::max(renderBounds->max.y, v1.y);
    renderBounds->max.y = glm::max(renderBounds->max.y, v2.y);
    renderBounds->max.y = glm::min((float)height-1, renderBounds->max.y);

    glm::vec3 color0 = colors->at(face.x);
    glm::vec3 color1 = colors->at(face.y);
    glm::vec3 color2 = colors->at(face.z);
    
    float area = InsideTriangle(v2, v1, v0);
    
    for(int i = (int)glm::floor(renderBounds->max.y); i > (int)glm::floor(renderBounds->min.y); i--)
    {
        for(int j = (int)glm::floor(renderBounds->min.x); j < (int)glm::floor(renderBounds->max.x); j++)
        {
            glm::vec2 p(j, i);

            // 2d cross product to determine
            float e0 = InsideTriangle(v2, v1, p);
            float e1 = InsideTriangle(v0, v2, p);
            float e2 = InsideTriangle(v1, v0, p);

            if(e0 >= 0 && e1 >= 0 && e2 >=0)
            {
                // interpolations based on barycentric coords
                float w0 = e0 / area;
                float w1 = e1 / area;
                float w2 = e2 / area;
                
                float r = w0 * color0.r + w1 * color1.r + w2 * color2.r;
                float g = w0 * color0.g + w1 * color1.g + w2 * color2.g;
                float b = w0 * color0.b + w1 * color1.b + w2 * color2.b;

                uint8_t red = r * 255;
                uint8_t green = g * 255;
                uint8_t blue = b * 255;

                colorBuffer[i][j] = (0xFF << 24 | red << 16 | green << 8 | blue);
            }
        }
    }
}

void Camera::RenderSceneToPixels(uint32_t* pixels)
{
    // clear the pixel buffer
    for(int i = 0; i < colorBuffer.size(); i++)
    {
        for(int j = 0; j < colorBuffer[i].size(); j++)
        {
            colorBuffer[i][j] = 0;
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
        std::vector<glm::vec3> objectColors;
        objectVerts.reserve(obj->mesh->verts.size());
        objectColors.reserve(obj->mesh->verts.size());
        
        // apply transformations
        for(Vertex v : obj->mesh->verts)
        {
            glm::vec4 newvert = {v.position.x, v.position.y, v.position.z, 1};
            newvert = MVP * newvert;
            newvert.x = (newvert.x/newvert.w + 1)/2 * width;
            newvert.y = (newvert.y*-1/newvert.w + 1)/2 * height;
            
            objectVerts.push_back(newvert);
            objectColors.push_back(v.color);
        }
        
        for(glm::ivec3 face : obj->mesh->faces)
        {
            DrawTriangle(&objectVerts, &objectColors, face);
        }
    }

    // write 2d camera buffer to 1d pixel buffer for SDL to draw
    for(int i = 0; i < colorBuffer.size(); i++)
    {
        for(int j = 0; j < colorBuffer[i].size(); j++)
        {
            pixels[Index(j, i)] = colorBuffer[i][j];
        }
    }
}