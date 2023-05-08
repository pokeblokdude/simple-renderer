#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"
#include "Renderer.h"
#include <iostream>
#include <chrono>

#include "world/Camera.h"
#include "world/Object.h"
#include "world/Scene.h"
#include "world/shapes/Cube.h"
#include "world/shapes/Quad.h"
#include "world/shapes/Triangle.h"

int main(int argc, char** argv)
{
    const int WIDTH = 100;
    const int HEIGHT = 100;
    
    SDL_SetMainReady();

    Renderer* renderer = new Renderer(WIDTH, HEIGHT, true);

    bool init = renderer->Initialize();
    if(!init)
    {
        std::cout << "SDL error during initialization." << std::endl;
        return 1;    
    }

    Scene* scene = new Scene();
    scene->objects.push_back(new Object((Mesh*)(new Quad())));
    scene->CreateCamera(60, WIDTH, HEIGHT, 0.1f, 1000);
    
    // render loop
    std::chrono::microseconds deltaTime;
    while(!renderer->quit)
    {
        std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::high_resolution_clock::now();
        if(deltaTime.count() != 0)
        {
            std::cout << 1000000 / deltaTime.count() << " fps / " << deltaTime.count() / (double)1000 << "ms" << std::endl;
        }

        renderer->PollEvents();
        scene->camera->RenderSceneToPixels(renderer->pixels);
        renderer->Draw();

        std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::high_resolution_clock::now();
        deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    }

    delete scene;
    delete renderer;
    return 0;
}
